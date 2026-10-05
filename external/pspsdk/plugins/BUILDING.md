# PSP JSON module builds on Windows

Use the same entry points as the PS2 SDK module builder:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File external/pspsdk/plugins/build-module.ps1 -Project source/module.json
powershell -NoProfile -ExecutionPolicy Bypass -File external/pspsdk/plugins/build-module.ps1 -Project source/module.json -Clean
```

Paths in `module.json` are relative to that file, regardless of the caller's
working directory. Projects may reside in folders containing spaces. Sources
are explicit; add new files to the manifest. C helpers always use the C compiler,
even in a C++ project. Assembly sources are supported too.

```json
{
  "sources": ["main.c", "includes/injector.c"],
  "output": "../data/memstick/PSP/PLUGINS/MyPlugin/MyPlugin.prx",
  "exports": "exports.exp",
  "startup": "module_start",
  "libraries": ["-lpspsystemctrl_user", "-lm"]
}
```

The common PS2/PSP fields are `sources`, `output`, `includes`, `defines` and
`link_options`. PSP additionally uses `exports`, `startup` and `libraries`.
Optional `c_flags` replaces the default C flags; `cxx_flags` supplies additional
C++ flags (defaults to disabling exceptions/RTTI), and `as_flags` adds assembly
flags. Unknown fields fail instead of silently ignoring a misspelling.

`startup: "module_start"` follows the existing `build_prx.mak` profile with no
CRT startup files. The plugin supplies `module_start`. This is the default and
preserves WidescreenFixesPack's C PRX behavior. `startup: "crt"` follows the
existing `build.mak` PRX profile, linking the SDK startup files so `main`, heap
initialization and C++ constructors work as before. PSP CLEO and C++ template
projects use this profile. C++ compilation alone does not change the startup
profile; choose it explicitly.

The builder generates exports into the output's private `.prx.objects` directory,
links an ELF, fixes imports and generates the PRX with the existing SDK utilities.
Each stage must succeed before replacing previous PRX/ELF/map outputs. It also
produces `.prx.map`; cleanup removes only those selected outputs and their private
objects. SDK files and other plugin outputs remain untouched. Full compilation
on each invocation avoids stale objects after manifest or flag changes.

No PPSSPP or game patches, plugin waits or runtime ABI are changed. The legacy
`vsmake.ps1` remains available for projects with their own SDK makefiles.

Run `python -B -m unittest discover -s plugins -p test_build.py -v` to verify real
C and C++ builds, paths with spaces, failed-build preservation and bounded clean.
