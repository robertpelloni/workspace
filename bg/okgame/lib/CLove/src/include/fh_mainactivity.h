/*
#   clove
#
#   Copyright (C) 2019-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef CLOVE_WEB
#include <emscripten.h>
#endif

#include "../3rdparty/FH/src/fh.h"
#include "../3rdparty/SDL2/include/SDL.h"
#include "../3rdparty/microtar/microtar.h"

#include "utils.h"
#include "graphics.h"
#include "particlesystem.h"
#include "matrixstack.h"
#include "filesystem.h"
#include "audio.h"
#include "streamsource.h"
#include "timer.h"
#include "love.h"
#include "joystick.h"
#include "keyboard.h"
#include "mouse.h"

void fh_main_activity_load(int argc, char* argv[]);
void fh_main_loop(int argc, char **argv);
