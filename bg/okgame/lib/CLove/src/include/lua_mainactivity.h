/*
#   clove
#
#   Copyright (C) 2017-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#ifdef CLOVE_WEB
#include <emscripten.h>
#endif

#include "../3rdparty/lua/lua.h"
#include "../3rdparty/lua/lauxlib.h"
#include "../3rdparty/lua/lualib.h"
#include "../3rdparty/SDL2/include/SDL.h"
#include "../3rdparty/microtar/microtar.h"

#include "../luaapi/audio.h"
#include "../luaapi/mouse.h"
#include "../luaapi/event.h"
#include "../luaapi/graphics.h"
#include "../luaapi/graphics_font.h"
#include "../luaapi/image.h"
#include "../luaapi/love.h"
#include "../luaapi/boot.h"
#include "../luaapi/joystick.h"
#include "../luaapi/keyboard.h"
#include "../luaapi/mouse.h"
#include "../luaapi/filesystem.h"
#include "../luaapi/timer.h"
#include "../luaapi/math.h"
#include "../luaapi/system.h"
#include "../luaapi/thread.h"
#include "../luaapi/net.h"
#include "../luaapi/errorhandler.h"

#include "utils.h"
#include "graphics.h"
#include "geometry.h"
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

/* Only if USE_NATIVE is declared in tools/utils.c
 * then use it */
#ifdef USE_NATIVE
#include "../../native/game.h"
#endif

void lua_main_activity_load(int argc, char* argv[]);
void lua_main_loop(void);

