#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::Data" for configuration "MinSizeRel"
set_property(TARGET Poco::Data APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Poco::Data PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/PocoData.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/PocoData.dll"
  )

list(APPEND _cmake_import_check_targets Poco::Data )
list(APPEND _cmake_import_check_files_for_Poco::Data "${_IMPORT_PREFIX}/lib/PocoData.lib" "${_IMPORT_PREFIX}/bin/PocoData.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
