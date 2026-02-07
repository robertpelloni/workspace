/*
#   clove
#
#   Copyright (C) 2017-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef USE_LUA

#include "../3rdparty/lua/lua.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int l_net_register(lua_State* state);

#endif
