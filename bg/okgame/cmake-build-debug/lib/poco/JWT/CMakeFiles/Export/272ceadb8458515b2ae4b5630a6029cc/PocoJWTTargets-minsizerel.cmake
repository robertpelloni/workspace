#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::JWT" for configuration "MinSizeRel"
set_property(TARGET Poco::JWT APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Poco::JWT PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/PocoJWT.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/PocoJWT.dll"
  )

list(APPEND _cmake_import_check_targets Poco::JWT )
list(APPEND _cmake_import_check_files_for_Poco::JWT "${_IMPORT_PREFIX}/lib/PocoJWT.lib" "${_IMPORT_PREFIX}/bin/PocoJWT.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
