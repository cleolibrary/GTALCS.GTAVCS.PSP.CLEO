#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "tinygettext::tinygettext" for configuration "Release"
set_property(TARGET tinygettext::tinygettext APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(tinygettext::tinygettext PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "/__w/psp-packages/psp-packages/tinygettext/pkg/tinygettext/psp/lib/libtinygettext.a"
  )

list(APPEND _cmake_import_check_targets tinygettext::tinygettext )
list(APPEND _cmake_import_check_files_for_tinygettext::tinygettext "/__w/psp-packages/psp-packages/tinygettext/pkg/tinygettext/psp/lib/libtinygettext.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
