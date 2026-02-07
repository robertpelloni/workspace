/*
#   clove
#
#   Copyright (C) 2016-2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#ifdef USE_LUA

#include "event.h"
#include "tools.h"

#include "../include/utils.h"

static int l_event_quit(lua_State* state) {
  clove_running = false;
  lua_pushinteger(state, l_running);
  return 1;
}

static int l_event_swap(lua_State* state) {
  swap_At = lua_tonumber(state, 1);
  return 1;
}

static luaL_Reg const regFuncs[] = {
  {"quit", l_event_quit},
  {"swap", l_event_swap},
  {NULL,NULL}
};

bool l_event_running() {
  return clove_running;
}

int l_event_register(lua_State* state) {

  clove_running = true;
  l_tools_registerModule(state, "event", regFuncs);
  return 1;
}

#endif
