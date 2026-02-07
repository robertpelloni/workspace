/*
#   clove
#
#   Copyright (C) 2016-2017 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_LUA

#include "../3rdparty/lua/lualib.h"

#include "love.h"

#include "../include/love.h"

int l_love_getVersion(lua_State* state) {
  love_Version const * version = love_getVersion();
  lua_pushnumber(state, version->major);
  lua_pushnumber(state, version->minor);
  lua_pushnumber(state, version->revision);
  lua_pushstring(state, version->codename);
  return 4;
}

int l_love_register(lua_State* state) {
  lua_newtable(state);

  lua_pushstring(state, "getVersion");
  lua_pushcfunction(state, l_love_getVersion);
  lua_rawset(state, -3);

  lua_setglobal(state, "love");

  luaL_openlibs(state);

  return 0;
}

#endif
