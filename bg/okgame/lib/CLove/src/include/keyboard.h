/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/SDL2/include/SDL_keyboard.h"

#include <stdbool.h>

void keyboard_init(void);
char const * keyboard_getKeyName(SDL_Keycode key);
void keyboard_keypressed(SDL_Keycode key);
void keyboard_keyreleased(SDL_Keycode key);
SDL_Keycode keyboard_getKeycode(char const* name);
bool keyboard_ispressed(SDL_Keycode key);
void keyboard_startText(void);
void keyboard_stopText(void);
bool keyboard_isTextEnabled(void);
void keyboard_textInput(char const* text);
