#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "expat::expat" for configuration ""
set_property(TARGET expat::expat APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(expat::expat PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "C"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libexpat.a"
  )

list(APPEND _cmake_import_check_targets expat::expat )
list(APPEND _cmake_import_check_files_for_expat::expat "${_IMPORT_PREFIX}/lib/libexpat.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
