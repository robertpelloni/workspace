#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::JSON" for configuration "MinSizeRel"
set_property(TARGET Poco::JSON APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Poco::JSON PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/PocoJSON.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/PocoJSON.dll"
  )

list(APPEND _cmake_import_check_targets Poco::JSON )
list(APPEND _cmake_import_check_files_for_Poco::JSON "${_IMPORT_PREFIX}/lib/PocoJSON.lib" "${_IMPORT_PREFIX}/bin/PocoJSON.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
