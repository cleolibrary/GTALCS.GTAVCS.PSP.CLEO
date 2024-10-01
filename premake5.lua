workspace "GTALCS.GTAVCS.PSP.CLEO"
   configurations { "Release", "Debug" }
   platforms { "Win64" }
   architecture "x64"
   location "build"
   objdir ("build/obj")
   buildlog ("build/log/%{prj.name}.log")
   cppdialect "C++latest"
   include "makefile.lua"
   
   kind "SharedLib"
   language "C++"
   targetdir "data/scripts"
   targetextension ".asi"
   characterset ("UNICODE")
   staticruntime "On"
   
   files { "source/*.h" }
   files { "source/*.cpp" }
   files { "Resources/*.rc" }
   includedirs { "source" }
   
   pbcommands = { 
      "setlocal EnableDelayedExpansion",
      --"set \"path=" .. (gamepath) .. "\"",
      "set file=$(TargetPath)",
      "FOR %%i IN (\"%file%\") DO (",
      "set filename=%%~ni",
      "set fileextension=%%~xi",
      "set target=!path!!filename!!fileextension!",
      "if exist \"!target!\" copy /y \"%%~fi\" \"!target!\"",
      ")" }

   function setpaths(gamepath, exepath, scriptspath)
      scriptspath = scriptspath or "scripts/"
      if (gamepath) then
         cmdcopy = { "set \"path=" .. gamepath .. scriptspath .. "\"" }
         table.insert(cmdcopy, pbcommands)
         postbuildcommands (cmdcopy)
         debugdir (gamepath)
         if (exepath) then
            debugcommand (gamepath .. exepath)
            dir, file = exepath:match'(.*/)(.*)'
            debugdir (gamepath .. (dir or ""))
         end
      end
      targetdir ("data/%{prj.name}/" .. scriptspath)
   end
   
   function setbuildpaths_psp(gamepath, exepath, scriptspath, pspsdkpath, sourcepath, prj_name)
      -- local pbcmd = {}
      -- for k,v in pairs(pbcommands) do
      --   pbcmd[k] = v
      -- end
      if (gamepath) then
        buildcommands {"setlocal EnableDelayedExpansion"}
        rebuildcommands {"setlocal EnableDelayedExpansion"}
        local ppsspppath = os.getenv "PPSSPPMemstick"
        if (ppsspppath == nil) then
            buildcommands {"set _PPSSPPMemstick=" .. gamepath .. "memstick/PSP"}
            rebuildcommands {"set _PPSSPPMemstick=" .. gamepath .. "memstick/PSP"}
        else
            buildcommands {"set _PPSSPPMemstick=!PPSSPPMemstick!"}
            rebuildcommands {"set _PPSSPPMemstick=!PPSSPPMemstick!"}
        end
         
        buildcommands {
        "powershell -ExecutionPolicy Bypass -File \"" .. pspsdkpath .. "\" -C \"" .. sourcepath .. "\"\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!\r\n" ..
        "if not defined _PPSSPPMemstick goto :eof\r\n" ..
        "if not exist !_PPSSPPMemstick! goto :eof\r\n" ..
        "if not exist !_PPSSPPMemstick!/PLUGINS/ mkdir !_PPSSPPMemstick!/PLUGINS/\r\n" ..
        "set target=!_PPSSPPMemstick!/PLUGINS/$(ProjectName)\r\n" ..
        "copy /y $(NMakeOutput) \"!target!\"\r\n"
        }
        rebuildcommands {
        "powershell -ExecutionPolicy Bypass -File \"" .. pspsdkpath .. "\" -C \"" .. sourcepath .. "\" clean\r\n" ..
        "powershell -ExecutionPolicy Bypass -File \"" .. pspsdkpath .. "\" -C \"" .. sourcepath .. "\"\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!\r\n" ..
        "if not defined _PPSSPPMemstick goto :eof\r\n" ..
        "if not exist !_PPSSPPMemstick! goto :eof\r\n" ..
        "set target=!_PPSSPPMemstick!/PLUGINS/$(ProjectName)\r\n" ..
        "copy /y $(NMakeOutput) \"!target!\"\r\n"
        }
        cleancommands {
        "setlocal EnableDelayedExpansion\r\n" ..
        "powershell -ExecutionPolicy Bypass -File \"" .. pspsdkpath .. "\" -C \"" .. sourcepath .. "\" clean\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!\r\n"
        }
        debugdir (gamepath)
        if (exepath) then
           debugcommand (gamepath .. exepath)
           dir, file = exepath:match'(.*/)(.*)'
           debugdir (gamepath .. (dir or ""))
        end
      end
      targetdir ("data/" .. scriptspath)
   end
   
   function setbuildpaths_ps2(gamepath, exepath, scriptspath, ps2sdkpath, sourcepath, prj_name)
      -- local pbcmd = {}
      -- for k,v in pairs(pbcommands) do
      --   pbcmd[k] = v
      -- end
      if (gamepath) then
        buildcommands {"setlocal EnableDelayedExpansion"}
        rebuildcommands {"setlocal EnableDelayedExpansion"}
        local pcsx2fpath = os.getenv "PCSX2FDir"
        if (pcsx2fpath == nil) then
            buildcommands {"set _PCSX2FDir=" .. gamepath}
            rebuildcommands {"set _PCSX2FDir=" .. gamepath}
        else
            buildcommands {"set _PCSX2FDir=!PCSX2FDir!"}
            rebuildcommands {"set _PCSX2FDir=!PCSX2FDir!"}
        end
        buildcommands {
        "powershell -ExecutionPolicy Bypass -File \"" .. ps2sdkpath .. "\" -C \"" .. sourcepath .. "\"\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!\r\n" ..
        "if not defined _PCSX2FDir goto :eof\r\n" ..
        "if not exist !_PCSX2FDir! goto :eof\r\n" ..
        "if not exist !_PCSX2FDir!/PLUGINS mkdir !_PCSX2FDir!/PLUGINS\r\n" ..
        "set target=!_PCSX2FDir!/PLUGINS/\r\n" ..
        "copy /y $(NMakeOutput) \"!target!\"\r\n"
        }
        rebuildcommands {
        "powershell -ExecutionPolicy Bypass -File \"" .. ps2sdkpath .. "\" -C \"" .. sourcepath .. "\" clean\r\n" ..
        "powershell -ExecutionPolicy Bypass -File \"" .. ps2sdkpath .. "\" -C \"" .. sourcepath .. "\"\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!\r\n" ..
        "if not defined _PCSX2FDir goto :eof\r\n" ..
        "if not exist !_PCSX2FDir! goto :eof\r\n" ..
        "if not exist !_PCSX2FDir!/PLUGINS mkdir !_PCSX2FDir!/PLUGINS\r\n" ..
        "set target=!_PCSX2FDir!/PLUGINS/\r\n" ..
        "copy /y $(NMakeOutput) \"!target!\"\r\n"
        }
        cleancommands {
        "setlocal EnableDelayedExpansion\r\n" ..
        "powershell -ExecutionPolicy Bypass -File \"" .. ps2sdkpath .. "\" -C \"" .. sourcepath .. "\" clean\r\n" ..
        "if !errorlevel! neq 0 exit /b !errorlevel!"
        }
         
         debugdir (gamepath)
         if (exepath) then
            debugcommand (gamepath .. exepath)
            dir, file = exepath:match'(.*/)(.*)'
            debugdir (gamepath .. (dir or ""))
         end
      end
      targetdir ("data/" .. scriptspath)
   end

   function add_pspsdk()
      includedirs { "external/pspsdk/usr/local/pspdev/psp/sdk/include" }
      includedirs { "external/pspsdk/usr/local/pspdev/bin" }
      files { "source/*.h", "source/*.c", "source/*.cpp", "source/makefile" }
   end

   function add_ps2sdk()
      includedirs { "external/ps2sdk/ps2sdk/ee" }
      files { "source/*.h", "source/*.c", "source/*.cpp", "source/makefile" }
   end

   filter "configurations:Debug*"
      defines "DEBUG"
      symbols "On"

   filter "configurations:Release*"
      defines "NDEBUG"
      optimize "On"


project "cleo"
   kind "Makefile"
   add_pspsdk()
   targetextension ".prx"
   setbuildpaths_psp("Z:/WFP/Games/PPSSPP/", "PPSSPPWindows64.exe", "memstick/PSP/PLUGINS/cleo/", "%{wks.location}/../external/pspsdk/vsmake.ps1", "%{wks.location}/../source/", "cleo")
   writemakefile_psp("cleo", "utils.o", "text.o", "libres.o", "armhook.o", "touch.o", "ui.o", "plugins.o", "pattern.o", "core.o", "mutex.o", "strutils.o", "memutils.o", "psplang.o")
