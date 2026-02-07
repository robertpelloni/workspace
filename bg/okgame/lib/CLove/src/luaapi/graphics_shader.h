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

#include "../include/shader.h"

typedef struct {
  graphics_Shader shader;
  int *referencedTextures;
} l_graphics_Shader;

//int l_graphics_newShader(lua_State* state);
void l_graphics_shader_register(lua_State *state);
bool l_graphics_isShader(lua_State* state, int index);
l_graphics_Shader* l_graphics_toShader(lua_State* state, int index);

#endif
