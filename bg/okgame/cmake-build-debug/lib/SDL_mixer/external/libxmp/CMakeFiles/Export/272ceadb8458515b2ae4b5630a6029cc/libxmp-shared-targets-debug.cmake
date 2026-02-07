#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libxmp::xmp_shared" for configuration "Debug"
set_property(TARGET libxmp::xmp_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libxmp::xmp_shared PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libxmp.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libxmp.dll"
  )

list(APPEND _cmake_import_check_targets libxmp::xmp_shared )
list(APPEND _cmake_import_check_files_for_libxmp::xmp_shared "${_IMPORT_PREFIX}/lib/libxmp.lib" "${_IMPORT_PREFIX}/bin/libxmp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
