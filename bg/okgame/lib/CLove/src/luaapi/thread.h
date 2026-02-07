/*
#   clove
#
#   Copyright (C) 2016-2017 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef USE_LUA

#include "../3rdparty/lua/lua.h"
#include "../3rdparty/lua/lauxlib.h"

typedef struct {
    SDL_Thread* thread;
    int data;
    int res;
    lua_State* L;
} thread_Data;

void l_thread_register(lua_State* state);

#endif
