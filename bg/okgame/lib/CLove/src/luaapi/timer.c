/*
#   clove
#
#   Copyright (C) 2016-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_LUA
#include "../3rdparty/lua/lauxlib.h"

#include "timer.h"
#include "tools.h"

#include "../include/timer.h"

int l_timer_step(lua_State* state) {
    (void)state;
    timer_step();
    return 0;
}

int l_timer_getTime(lua_State* state) {
    lua_pushnumber(state, timer_getTime());
    return 1;
}

int l_timer_getFPS(lua_State* state) {
    lua_pushnumber(state, (int)(timer_getFPS()+0.5f));
    return 1;
}

int l_timer_getDelta(lua_State* state) {
    lua_pushnumber(state, timer_getDelta());
    return 1;
}

int l_timer_getAverageDelta(lua_State* state) {
    lua_pushnumber(state, timer_getAverageDelta());
    return 1;
}

int l_timer_sleep(lua_State* state) {
    float seconds = lua_tonumber(state, 1);
    timer_sleep(seconds);
    return 1;
}

static luaL_Reg const regFuncs[] = {
    {"getAverageDelta", l_timer_getAverageDelta},
    {"getDelta",        l_timer_getDelta},
    {"getFPS",          l_timer_getFPS},
    {"getTime",         l_timer_getTime},
    {"sleep",           l_timer_sleep},
    {"step",            l_timer_step},
    {NULL, NULL}
};

void l_timer_register(lua_State* state) {
    l_tools_registerModule(state, "timer", regFuncs);
}

#endif
