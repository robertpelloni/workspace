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

#include "../include/audio.h"
#include "../include/staticsource.h"
#include "../include/streamsource.h"

int l_audio_register(lua_State *state);
bool l_audio_isStaticSource(lua_State* state, int index);
bool l_audio_isStreamSource(lua_State* state, int index);

#endif
