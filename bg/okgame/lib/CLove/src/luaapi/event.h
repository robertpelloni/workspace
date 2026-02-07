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

#include <stdbool.h>

#include "../3rdparty/lua/lua.h"

int l_event_register(lua_State* state);
bool l_event_running();

bool l_running;
float swap_At;

#endif
