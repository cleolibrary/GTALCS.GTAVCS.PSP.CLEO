#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "zziplib::libzzip" for configuration "Release"
set_property(TARGET zziplib::libzzip APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(zziplib::libzzip PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libzzip-0.a"
  )

list(APPEND _cmake_import_check_targets zziplib::libzzip )
list(APPEND _cmake_import_check_files_for_zziplib::libzzip "${_IMPORT_PREFIX}/lib/libzzip-0.a" )

# Import target "zziplib::libzzipfseeko" for configuration "Release"
set_property(TARGET zziplib::libzzipfseeko APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(zziplib::libzzipfseeko PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libzzipfseeko-0.a"
  )

list(APPEND _cmake_import_check_targets zziplib::libzzipfseeko )
list(APPEND _cmake_import_check_files_for_zziplib::libzzipfseeko "${_IMPORT_PREFIX}/lib/libzzipfseeko-0.a" )

# Import target "zziplib::libzzipmmapped" for configuration "Release"
set_property(TARGET zziplib::libzzipmmapped APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(zziplib::libzzipmmapped PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libzzipmmapped-0.a"
  )

list(APPEND _cmake_import_check_targets zziplib::libzzipmmapped )
list(APPEND _cmake_import_check_files_for_zziplib::libzzipmmapped "${_IMPORT_PREFIX}/lib/libzzipmmapped-0.a" )

# Import target "zziplib::libzzipwrap" for configuration "Release"
set_property(TARGET zziplib::libzzipwrap APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(zziplib::libzzipwrap PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libzzipwrap-0.a"
  )

list(APPEND _cmake_import_check_targets zziplib::libzzipwrap )
list(APPEND _cmake_import_check_files_for_zziplib::libzzipwrap "${_IMPORT_PREFIX}/lib/libzzipwrap-0.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
