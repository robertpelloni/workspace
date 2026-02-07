#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::ActiveRecord" for configuration "RelWithDebInfo"
set_property(TARGET Poco::ActiveRecord APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Poco::ActiveRecord PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/PocoActiveRecord.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/PocoActiveRecord.dll"
  )

list(APPEND _cmake_import_check_targets Poco::ActiveRecord )
list(APPEND _cmake_import_check_files_for_Poco::ActiveRecord "${_IMPORT_PREFIX}/lib/PocoActiveRecord.lib" "${_IMPORT_PREFIX}/bin/PocoActiveRecord.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
