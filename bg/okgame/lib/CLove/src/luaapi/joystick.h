/*
#   clove
#
#   Copyright (C) 2016-2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef USE_LUA

#include "../3rdparty/lua/lua.h"

#include "../include/joystick.h"

typedef struct {
    joystick_Joystick* joystick;
} l_joystick_Joystick;

void l_joystick_register(lua_State* state);

void l_joystick_pressed(int id, int button);
void l_joystick_released(int id, int button);

#endif
