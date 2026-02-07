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

void l_mouse_register(lua_State* state);
void l_mouse_pressed(int x, int y, int button);
void l_mouse_released(int x, int y, int button);
void l_mouse_wheelmoved(int y);

#endif
