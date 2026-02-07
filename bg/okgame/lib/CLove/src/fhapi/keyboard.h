/*
#   clove
#
#   Copyright (C) 2016-2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/FH/src/fh.h"

#include "../3rdparty/SDL2/include/SDL_keycode.h"

#include <stdbool.h>

void fh_keyboard_register(struct fh_program *prog);
int fh_keyboard_keypressed(SDL_Keycode key, bool repeat);
int fh_keyboard_keyreleased(SDL_Keycode key);
int fh_keyboard_textInput(char const* text);
