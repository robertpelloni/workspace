/*
#   clove
#
#   Copyright (C) 2016-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/lua/lua.h"

#include "../include/imagedata.h"

#include <stdbool.h>

bool l_image_isImageData(lua_State* state, int index);
image_ImageData* l_image_toImageData(lua_State* state, int index);
int l_image_register(lua_State* state);
int l_image_newImageData(lua_State* state);
image_ImageData* l_image_getImageData();
