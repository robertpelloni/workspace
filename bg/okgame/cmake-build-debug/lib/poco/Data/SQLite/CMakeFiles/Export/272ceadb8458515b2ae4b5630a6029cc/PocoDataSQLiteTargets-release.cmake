#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::DataSQLite" for configuration "Release"
set_property(TARGET Poco::DataSQLite APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Poco::DataSQLite PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/PocoDataSQLite.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/PocoDataSQLite.dll"
  )

list(APPEND _cmake_import_check_targets Poco::DataSQLite )
list(APPEND _cmake_import_check_files_for_Poco::DataSQLite "${_IMPORT_PREFIX}/lib/PocoDataSQLite.lib" "${_IMPORT_PREFIX}/bin/PocoDataSQLite.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
