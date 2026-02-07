/*
#   clove
#
#   Copyright (C) 2016-2018 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_LUA

#include <stdlib.h>
#include <stdio.h>

#include "../3rdparty/lua/lauxlib.h"
#include "../3rdparty/SDL2/include/SDL_thread.h"
#include "../3rdparty/SDL2/include/SDL_timer.h"

#include "thread.h"
#include "tools.h"

static struct {
    int threadDataMT;
    lua_State* state;
} moduleData;

static int callback(void* ptr) {
    lua_State* L = moduleData.state;

    if (luaL_checkstring(L, 1)) {
        luaL_loadfile(L, lua_tostring(L, 1));
        if (lua_pcall(L, 0,0,0) != 0)
            luaL_error(L, "%s \n", lua_tostring(L, -1));
    }else {
        luaL_error(L, "Error in thread. Only .lua file is correct %s %\n", lua_tostring(L, -1));
        return -1;
    }
    return 1;
}

static int l_thread_newThread(lua_State* state) {
    thread_Data* data = (thread_Data*) lua_newuserdata(state, sizeof(thread_Data));
    moduleData.state = state;

    const char* name = luaL_optstring(state, 2, NULL);
    data->thread = SDL_CreateThread((SDL_ThreadFunction)callback, name, (void *)NULL);

    if (NULL == data->thread)
        luaL_error(state, "\n Create thread failed: %s\n", SDL_GetError());
    else
        SDL_WaitThread(data->thread, &data->res);

    lua_rawgeti(state, LUA_REGISTRYINDEX, moduleData.threadDataMT);
    lua_setmetatable(state, -2);

    return 1;
}
/*
static int l_thread_getThreadID(lua_State* state) {
    thread_Data* thread = (thread_Data*)lua_touserdata(state, 1);
    lua_pushinteger(state, SDL_GetThreadID(thread->thread));
    return 1;
}

static int l_thread_getThreadName(lua_State* state) {
    thread_Data* thread = (thread_Data*)lua_touserdata(state, 1);
    lua_pushstring(state, SDL_GetThreadName(thread->thread));
    return 1;
}
*/
static int l_thread_gcThread(lua_State* state) {
    thread_Data* thread = (thread_Data*)lua_touserdata(state, 1);
    SDL_DetachThread(thread->thread);
    return 1;
}

static luaL_Reg const regFuncs[] = {
    {"newThread", l_thread_newThread},
    //{"getID", l_thread_getThreadID},
    //{"getName", l_thread_getThreadName},
    {"__gc", l_thread_gcThread},
    {NULL, NULL}
};

void l_thread_register(lua_State* state) {
    l_tools_registerModule(state, "thread", regFuncs);
}

#endif
