#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "harfbuzz::harfbuzz" for configuration ""
set_property(TARGET harfbuzz::harfbuzz APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(harfbuzz::harfbuzz PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libharfbuzz.a"
  )

list(APPEND _cmake_import_check_targets harfbuzz::harfbuzz )
list(APPEND _cmake_import_check_files_for_harfbuzz::harfbuzz "${_IMPORT_PREFIX}/lib/libharfbuzz.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
