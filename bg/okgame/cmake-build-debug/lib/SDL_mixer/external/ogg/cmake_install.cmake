# Install script for directory: C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/bobsgame")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/Debug/ogg.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/Release/ogg.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/MinSizeRel/ogg.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/RelWithDebInfo/ogg.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/bin/Debug/ogg-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/bin/Release/ogg-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/bin/MinSizeRel/ogg-0.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/bin/RelWithDebInfo/ogg-0.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/ogg.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/SDL2_mixer/html" TYPE FILE FILES
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/framing.html"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/index.html"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/oggstream.html"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/ogg-multiplex.html"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/fish_xiph_org.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/multiplex1.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/packets.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/pages.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/stream.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/vorbisword2.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/white-ogg.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/white-xifish.png"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/rfc3533.txt"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/rfc5334.txt"
    "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/skeleton.html"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/SDL2_mixer/html" TYPE DIRECTORY FILES "C:/Users/hyper/workspace/okgame/lib/SDL_mixer/external/ogg/doc/libogg")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/hyper/workspace/okgame/cmake-build-debug/lib/SDL_mixer/external/ogg/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
