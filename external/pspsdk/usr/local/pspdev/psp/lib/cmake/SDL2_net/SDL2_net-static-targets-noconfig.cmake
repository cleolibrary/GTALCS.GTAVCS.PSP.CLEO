#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "SDL2_net::SDL2_net-static" for configuration ""
set_property(TARGET SDL2_net::SDL2_net-static APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(SDL2_net::SDL2_net-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libSDL2_net.a"
  )

list(APPEND _cmake_import_check_targets SDL2_net::SDL2_net-static )
list(APPEND _cmake_import_check_files_for_SDL2_net::SDL2_net-static "${_IMPORT_PREFIX}/lib/libSDL2_net.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
