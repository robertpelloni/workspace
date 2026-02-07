#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::DataSQLite" for configuration "Debug"
set_property(TARGET Poco::DataSQLite APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Poco::DataSQLite PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/PocoDataSQLited.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/PocoDataSQLited.dll"
  )

list(APPEND _cmake_import_check_targets Poco::DataSQLite )
list(APPEND _cmake_import_check_files_for_Poco::DataSQLite "${_IMPORT_PREFIX}/lib/PocoDataSQLited.lib" "${_IMPORT_PREFIX}/bin/PocoDataSQLited.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
