#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL2_mixer::SDL2_mixer-static" for configuration ""
set_property(TARGET SDL2_mixer::SDL2_mixer-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(SDL2_mixer::SDL2_mixer-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libSDL2_mixer.a"
  )

list(APPEND _cmake_import_check_targets SDL2_mixer::SDL2_mixer-static )
list(APPEND _cmake_import_check_files_for_SDL2_mixer::SDL2_mixer-static "${_IMPORT_PREFIX}/lib/libSDL2_mixer.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
