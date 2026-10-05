[CmdletBinding()]
param([Parameter(Mandatory)][string]$Project, [switch]$Clean)
$ErrorActionPreference = 'Stop'
$sdkRoot = Split-Path -Parent $PSScriptRoot
$projectPath = (Resolve-Path -LiteralPath $Project).Path
$projectDirectory = Split-Path -Parent $projectPath
$config = Get-Content -LiteralPath $projectPath -Raw | ConvertFrom-Json
$allowed = @('sources', 'output', 'exports', 'startup', 'includes', 'defines', 'libraries', 'c_flags', 'cxx_flags', 'as_flags', 'link_options')
foreach ($property in $config.PSObject.Properties.Name) {
    if ($property -notin $allowed) { throw "Unknown module.json field: $property" }
}
if (!$config.sources -or !$config.output -or !$config.exports) { throw 'Specify sources, output and exports in module.json.' }
$outputPath = [IO.Path]::GetFullPath((Join-Path $projectDirectory $config.output))
if ([IO.Path]::GetExtension($outputPath) -ne '.prx') { throw 'PSP module output must be a .prx file.' }
$elfPath = [IO.Path]::ChangeExtension($outputPath, '.elf')
$mapPath = $outputPath + '.map'
$objectDirectory = $outputPath + '.objects'
if ($Clean) {
    # The resolved output selects its own sibling object directory. No source or
    # shared SDK directories are ever passed to a recursive cleanup.
    if ([IO.Path]::GetFullPath($objectDirectory) -ne $outputPath + '.objects') { throw 'Invalid object directory' }
    Remove-Item -LiteralPath $objectDirectory -Recurse -Force -ErrorAction SilentlyContinue
    Remove-Item -LiteralPath $outputPath, $elfPath, $mapPath, ($outputPath + '.tmp'), ($elfPath + '.tmp'), ($mapPath + '.tmp') -Force -ErrorAction SilentlyContinue
    return
}
$sources = @($config.sources | ForEach-Object { (Resolve-Path -LiteralPath (Join-Path $projectDirectory $_)).Path })
$exports = (Resolve-Path -LiteralPath (Join-Path $projectDirectory $config.exports)).Path
$startup = $config.startup
if (!$startup) { $startup = 'module_start' }
if ($startup -notin @('module_start', 'crt')) { throw 'startup must be module_start or crt.' }
$toolDirectory = Join-Path $sdkRoot 'usr/local/pspdev/bin'
$sdk = Join-Path $sdkRoot 'usr/local/pspdev/psp/sdk'
$dev = Join-Path $sdkRoot 'usr/local/pspdev'
function Tool([string]$Name) {
    $result = Join-Path $toolDirectory ($Name + '.exe')
    if (!(Test-Path -LiteralPath $result)) { throw "PSP tool missing: $result" }
    return $result
}
function UnixPath([string]$Path) {
    # This SDK ships Cygwin tools. Drive paths become POSIX paths so its GCC
    # subprocesses and PSP utilities agree, including paths containing spaces.
    $full = [IO.Path]::GetFullPath($Path).Replace('\', '/')
    if ($full -notmatch '^([A-Za-z]):/') { throw "PSP toolchain requires a drive path: $Path" }
    return '/cygdrive/' + $Matches[1].ToLowerInvariant() + $full.Substring(2)
}
$gcc = Tool 'psp-gcc'
$gxx = Tool 'psp-g++'
$exportTool = Tool 'psp-build-exports'
$fixup = Tool 'psp-fixup-imports'
$prxgen = Tool 'psp-prxgen'
New-Item -ItemType Directory -Force -Path (Split-Path -Parent $outputPath), $objectDirectory | Out-Null
$originalPath, $originalDev, $originalSdk = $env:PATH, $env:PSPDEV, $env:PSPSDK
try {
    $env:PATH = (Join-Path $sdkRoot 'bin') + ';' + $toolDirectory + ';' + $originalPath
    $env:PSPDEV = UnixPath $dev
    $env:PSPSDK = UnixPath $sdk
    $flags = @('-O2', '-Os', '-G0', '-Wall', '-fshort-wchar', '-fno-pic', '-mno-check-zero-division', '-mpreferred-stack-boundary=4', '-fpack-struct=16')
    if ($config.PSObject.Properties.Name -contains 'c_flags') { $flags = @($config.c_flags) }
    $flags += '-D_PSP_FW_VERSION=150'
    foreach ($include in @($projectDirectory, (Join-Path $dev 'psp/include'), (Join-Path $sdk 'include'))) { $flags += '-I' + (UnixPath $include) }
    foreach ($include in $config.includes) { $flags += '-I' + (UnixPath (Join-Path $projectDirectory $include)) }
    foreach ($define in $config.defines) { $flags += '-D' + $define }
    $cppFlags = @('-fno-exceptions', '-fno-rtti')
    if ($config.PSObject.Properties.Name -contains 'cxx_flags') { $cppFlags = @($config.cxx_flags) }
    $objects = @()
    $hasCpp = $false
    $index = 0
    foreach ($source in $sources) {
        $extension = [IO.Path]::GetExtension($source)
        $compiler, $compileFlags = $gcc, $flags
        if ($extension -in @('.cpp', '.cc', '.cxx')) {
            $hasCpp = $true
            $compiler = $gxx
            $compileFlags += $cppFlags
        } elseif ($extension -in @('.s', '.S')) {
            $compileFlags += @($config.as_flags)
        } elseif ($extension -ne '.c') { throw "Unsupported PSP source: $source" }
        $object = Join-Path $objectDirectory ($index.ToString() + '-' + [IO.Path]::GetFileNameWithoutExtension($source) + '.o')
        & $compiler @compileFlags '-c' (UnixPath $source) '-o' (UnixPath $object)
        if ($LASTEXITCODE) { throw "Compilation failed: $source" }
        $objects += UnixPath $object
        ++$index
    }
    $exportSource = Join-Path $objectDirectory 'exports.c'
    $exportLines = & $exportTool '-b' (UnixPath $exports)
    if ($LASTEXITCODE) { throw 'PSP export generation failed.' }
    [IO.File]::WriteAllLines($exportSource, [string[]]$exportLines, (New-Object Text.UTF8Encoding($false)))
    $exportObject = Join-Path $objectDirectory 'exports.o'
    & $gcc @flags '-c' (UnixPath $exportSource) '-o' (UnixPath $exportObject)
    if ($LASTEXITCODE) { throw 'PSP export compilation failed.' }
    $objects += UnixPath $exportObject
    $linkFlags = @('-G0', ('-L' + (UnixPath $projectDirectory)), ('-L' + (UnixPath (Join-Path $dev 'psp/lib'))), ('-L' + (UnixPath (Join-Path $sdk 'lib'))), '-Wl,-q', ('-Wl,-T' + (UnixPath (Join-Path $sdk 'lib/linkfile.prx'))), '-Wl,-zmax-page-size=128', ('-Wl,-Map,' + (UnixPath ($mapPath + '.tmp'))))
    if ($startup -eq 'crt') { $linkFlags += '-specs=' + (UnixPath (Join-Path $sdk 'lib/prxspecs')) }
    else { $linkFlags += '-nostartfiles' }
    $libraries = @($config.libraries)
    if ($hasCpp -and '-lstdc++' -notin $libraries) { $libraries = @('-lstdc++') + $libraries }
    $libraries += @('-lpspdebug', '-lpspdisplay', '-lpspge', '-lpspctrl')
    if ($startup -eq 'crt') { $libraries += @('-lpspnet', '-lpspnet_apctl') }
    & $gcc @flags @linkFlags @objects @($config.link_options) @libraries '-o' (UnixPath ($elfPath + '.tmp'))
    if ($LASTEXITCODE) { throw 'PSP module link failed.' }
    & $fixup (UnixPath ($elfPath + '.tmp'))
    if ($LASTEXITCODE) { throw 'PSP import fixup failed.' }
    & $prxgen (UnixPath ($elfPath + '.tmp')) (UnixPath ($outputPath + '.tmp'))
    if ($LASTEXITCODE) { throw 'PSP PRX generation failed.' }
    $prx = [IO.File]::ReadAllBytes($outputPath + '.tmp')
    if ($prx.Length -lt 52 -or [Text.Encoding]::ASCII.GetString($prx, 1, 3) -ne 'ELF' -or $prx[0] -ne 127 -or [BitConverter]::ToUInt16($prx, 18) -ne 8) { throw 'Expected a MIPS ELF PRX.' }
    # Keep the installed PRX, ELF and map until every build stage has succeeded.
    Move-Item -LiteralPath ($elfPath + '.tmp') -Destination $elfPath -Force
    Move-Item -LiteralPath ($mapPath + '.tmp') -Destination $mapPath -Force
    Move-Item -LiteralPath ($outputPath + '.tmp') -Destination $outputPath -Force
    Write-Host "Built PSP module: $outputPath"
} finally {
    $env:PATH, $env:PSPDEV, $env:PSPSDK = $originalPath, $originalDev, $originalSdk
    Remove-Item -LiteralPath ($outputPath + '.tmp'), ($elfPath + '.tmp'), ($mapPath + '.tmp') -Force -ErrorAction SilentlyContinue
}
