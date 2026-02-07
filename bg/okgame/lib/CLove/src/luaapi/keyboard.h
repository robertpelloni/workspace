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
#include "../3rdparty/SDL2/include/SDL_keycode.h"

#include <stdbool.h>

void l_keyboard_register(lua_State* state);
void l_keyboard_keypressed(SDL_Keycode key, bool repeat);
void l_keyboard_keyreleased(SDL_Keycode key);
void l_keyboard_textInput(char const* text);

#endif
