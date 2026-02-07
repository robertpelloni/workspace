/*
#   clove
#
#   Copyright (C) 2016-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef USE_LUA

#include "../3rdparty/lua/lua.h"

#include "../include/batch.h"
#include <stdbool.h>

typedef struct {
  graphics_Batch batch;
  int textureRef;
} l_graphics_Batch;

int l_graphics_newSpriteBatch(lua_State* state);
void l_graphics_batch_register(lua_State* state);
bool l_graphics_isBatch(lua_State* state, int index);
l_graphics_Batch* l_graphics_toBatch(lua_State* state, int index);

#endif
