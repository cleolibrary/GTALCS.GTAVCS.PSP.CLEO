$scriptDirectory = Split-Path -Parent $MyInvocation.MyCommand.Path
$usrBinPath = Join-Path -Path $scriptDirectory -ChildPath "/bin"
$pspsdkBinPath = Join-Path -Path $scriptDirectory -ChildPath "/usr/local/pspdev/bin"
$env:PSPDEV = "/usr/local/pspdev"
$env:PATH = "$usrBinPath;$pspsdkBinPath;$env:PATH"
make $args
exit $LASTEXITCODE