#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Ogg::ogg" for configuration ""
set_property(TARGET Ogg::ogg APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Ogg::ogg PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libogg.a"
  )

list(APPEND _cmake_import_check_targets Ogg::ogg )
list(APPEND _cmake_import_check_files_for_Ogg::ogg "${_IMPORT_PREFIX}/lib/libogg.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
