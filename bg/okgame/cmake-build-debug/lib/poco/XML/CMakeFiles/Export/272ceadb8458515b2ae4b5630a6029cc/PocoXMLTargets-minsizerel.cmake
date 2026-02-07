#----------------------------------------------------------------
# Generated CMake target import file for configuration "MinSizeRel".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Poco::XML" for configuration "MinSizeRel"
set_property(TARGET Poco::XML APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(Poco::XML PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "${_IMPORT_PREFIX}/lib/PocoXML.lib"
  IMPORTED_LOCATION_MINSIZEREL "${_IMPORT_PREFIX}/bin/PocoXML.dll"
  )

list(APPEND _cmake_import_check_targets Poco::XML )
list(APPEND _cmake_import_check_files_for_Poco::XML "${_IMPORT_PREFIX}/lib/PocoXML.lib" "${_IMPORT_PREFIX}/bin/PocoXML.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
