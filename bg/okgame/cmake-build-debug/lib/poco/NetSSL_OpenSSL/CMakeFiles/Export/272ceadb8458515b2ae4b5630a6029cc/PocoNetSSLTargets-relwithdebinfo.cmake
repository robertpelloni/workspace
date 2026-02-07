#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::NetSSL" for configuration "RelWithDebInfo"
set_property(TARGET Poco::NetSSL APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Poco::NetSSL PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/PocoNetSSL.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/PocoNetSSL.dll"
  )

list(APPEND _cmake_import_check_targets Poco::NetSSL )
list(APPEND _cmake_import_check_files_for_Poco::NetSSL "${_IMPORT_PREFIX}/lib/PocoNetSSL.lib" "${_IMPORT_PREFIX}/bin/PocoNetSSL.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
