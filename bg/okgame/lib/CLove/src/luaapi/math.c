/*
#   clove
#
#   Copyright (C) 2016-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_LUA

#include "tools.h"
#include "math.h"

#include "../include/minmax.h"
#include "../include/random.h"

#include "../3rdparty/noise/simplexnoise.h"

int l_math_random(lua_State* state) {
  float lo = 0.0f, hi = 1.0f;
  int t = lua_gettop(state);
  switch(t) {

    case 0:
      lo = 0;
      hi = 1;
      break;

    case 1:
      lo = 1;
      hi = l_tools_toNumberOrError(state, 1);
      break;

    case 2:
      lo = l_tools_toNumberOrError(state, 1);
      hi = l_tools_toNumberOrError(state, 2);
      break;
    }

  lua_pushnumber(state, math_random(lo, hi));
  return 1;
}

int l_math_random_setSeed(lua_State* state) {
  double value = l_tools_toNumberOrError(state, 1);
  math_random_setSeed(value);
  return 0;
}

int l_math_max(lua_State* state) {
  float x = l_tools_toNumberOrError(state, 1);
  float y = l_tools_toNumberOrError(state, 2);
  float result = max(x,y);
  lua_pushnumber(state, result);
  return 1;
}

int l_math_min(lua_State* state) {
  float x = l_tools_toNumberOrError(state, 1);
  float y = l_tools_toNumberOrError(state, 2);
  float result = min(x,y);
  lua_pushnumber(state, result);
  return 1;
}

int l_math_clamp(lua_State* state) {
  float a = l_tools_toNumberOrError(state, 1);
  float x = l_tools_toNumberOrError(state, 1);
  float y = l_tools_toNumberOrError(state, 2);
  float result = clamp(a, x, y);
  lua_pushnumber(state, result);
  return 1;
}

static int l_math_noise(lua_State* state) {
  float a[4];
  float r;

  int t = min(lua_gettop(state), 4);

  for(int i = 0; i < t; ++i) {
      a[i] = l_tools_toNumberOrError(state, i+1);
    }

  switch(t) {
    case 1:
      r = simplexnoise_noise1(a[0]);
      break;

    case 2:
      r = simplexnoise_noise2(a[0], a[1]);
      break;

    case 3:
      r = simplexnoise_noise3(a[0], a[1], a[2]);
      break;

    case 4:
      r = simplexnoise_noise4(a[0], a[1], a[2], a[3]);
      break;

    default:
      lua_pushstring(state, "need at least one dimension");
      return lua_error(state);
    }

  lua_pushnumber(state, r);
  return 1;
}

static luaL_Reg const mathFreeFuncs[] = {
  {"noise", l_math_noise},
  {"random", l_math_random},
  {"setRandomSeed", l_math_random_setSeed},
  {"max", l_math_max},
  {"min", l_math_min},
  {"clamp", l_math_clamp},
  {NULL, NULL}
};

void l_math_register(lua_State* state) {
  l_tools_registerModule(state, "math", mathFreeFuncs);
}

#endif
