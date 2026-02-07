#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::Redis" for configuration "MinSizeRel"
set_property(TARGET Poco::Redis APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Poco::Redis PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/PocoRedis.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/PocoRedis.dll"
  )

list(APPEND _cmake_import_check_targets Poco::Redis )
list(APPEND _cmake_import_check_files_for_Poco::Redis "${_IMPORT_PREFIX}/lib/PocoRedis.lib" "${_IMPORT_PREFIX}/bin/PocoRedis.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
