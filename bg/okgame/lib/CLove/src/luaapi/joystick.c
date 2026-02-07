/*
#   clove
#
#   Copyright (C) 2016-2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_LUA

#include <stdlib.h>
#include <string.h>

#include "joystick.h"
#include "tools.h"

static struct {
    lua_State *luaState;
    int count;
    int joystickDataMT;
} moduleData;


static int l_joystick_isDown(lua_State *state) {
    int id = lua_tointeger(state, 1);
    int top = lua_gettop(state);
    bool any = false;
    for (int i = 1; i < top; i++) {
        int button = joystick_convert_str_to_button(lua_tostring(state, i + 1));
        joystick_Joystick *js = joystick_get(id);
        any = joystick_isDown(js, button);
        if (any)
            break;
    }
    lua_pushboolean(state, any);
    return 1;
}

void l_joystick_pressed(int id, int button) {
    lua_getglobal(moduleData.luaState, "love");
    lua_pushstring(moduleData.luaState, "joystickpressed");
    lua_rawget(moduleData.luaState, -2);
    lua_pushinteger(moduleData.luaState, id);
    lua_pushstring(moduleData.luaState, joystick_convert_button_to_str(button));
    lua_call(moduleData.luaState, 2, 0);
}

void l_joystick_released(int id, int button) {
    lua_getglobal(moduleData.luaState, "love");
    lua_pushstring(moduleData.luaState, "joystickreleased");
    lua_rawget(moduleData.luaState, -2);
    lua_pushinteger(moduleData.luaState, id);
    lua_pushstring(moduleData.luaState, joystick_convert_button_to_str(button));
    lua_call(moduleData.luaState, 2, 0);
}

static int l_joystick_getNumAxes(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushnumber(state, joystick_getNumAxes(js));
    return 1;
}

static int l_joystick_getAxis(lua_State *state) {
    int id = lua_tointeger(state, 1);
    int axis = 0;
    int size = 0;
    joystick_Joystick *js = joystick_get(id);

    axis = lua_tointeger(state, 2);
    lua_pushnumber(state, joystick_getAxis(js, axis));

    return 1;
}

static int l_joystick_getJoystickCount(lua_State *state) {
    lua_pushnumber(state, joystick_getCount());
    return 1;
}

static int l_joystick_getHatCount(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushinteger(state, joystick_getHatCount(js));
    return 1;
}

static int fromCharHatToInt(const char *v) {
    if (strncmp(v, "c", 1) == 0)
        return SDL_HAT_CENTERED;
    if (strncmp(v, "d", 1) == 0)
        return SDL_HAT_DOWN;
    if (strncmp(v, "l", 1) == 0)
        return SDL_HAT_LEFT;
    if (strncmp(v, "ld", 2) == 0)
        return SDL_HAT_LEFTDOWN;
    if (strncmp(v, "lu", 2) == 0)
        return SDL_HAT_LEFTUP;
    if (strncmp(v, "r", 1) == 0)
        return SDL_HAT_RIGHT;
    if (strncmp(v, "rd", 2) == 0)
        return SDL_HAT_RIGHTDOWN;
    if (strncmp(v, "ru", 2) == 0)
        return SDL_HAT_RIGHTUP;
    if (strncmp(v, "u", 1) == 0)
        return SDL_HAT_UP;

    return SDL_HAT_CENTERED;
}

static int l_joystick_getHat(lua_State *state) {
    int id = lua_tonumber(state, 1);
    joystick_Joystick *js = joystick_get(id);
    int hat = fromCharHatToInt(lua_tostring(state, 2));
    int dir = joystick_getHat(js, hat);
    lua_pushboolean(state, hat == dir);
    return 1;
}

static int l_joystick_getName(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushstring(state, joystick_getName(js));
    return 1;
}

static int l_joystick_isConnected(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushboolean(state, joystick_isConnected(js));
    return 1;
}

static int l_joystick_isGamepad(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushboolean(state, joystick_isGamepad(js));
    return 1;
}

static int l_joystick_getBallsCount(lua_State *state) {
    int id = lua_tointeger(state, 1);
    joystick_Joystick *js = joystick_get(id);
    lua_pushinteger(state, joystick_getNumButtons(js));
    return 1;
}

static float returnGamepadAxis(const char *v) {
    if (strncmp(v, "leftx", 5) == 0)
        return SDL_CONTROLLER_AXIS_LEFTX;
    if (strncmp(v, "lefty", 5) == 0)
        return SDL_CONTROLLER_AXIS_LEFTY;
    if (strncmp(v, "rightx", 6) == 0)
        return SDL_CONTROLLER_AXIS_RIGHTX;
    if (strncmp(v, "righty", 6) == 0)
        return SDL_CONTROLLER_AXIS_RIGHTY;
    if (strncmp(v, "left_trigger", 12) == 0)
        return SDL_CONTROLLER_AXIS_TRIGGERLEFT;
    if (strncmp(v, "right_trigger", 13) == 0)
        return SDL_CONTROLLER_AXIS_TRIGGERRIGHT;
    return SDL_CONTROLLER_AXIS_INVALID;
}

static int l_joystick_getGamepadAxis(lua_State *state) {
    int id = lua_tointeger(state, 1);
    float get_axis = returnGamepadAxis(lua_tostring(state, 2));
    joystick_Joystick *js = joystick_get(id);

    float return_axis = joystick_getGamepadAxis(js, get_axis);

    lua_pushboolean(state, get_axis == return_axis);
    return 1;
}

static luaL_Reg const regFuncs[] = {
    {"getGamepadAxis", l_joystick_getGamepadAxis},
    {"getBallsCount", l_joystick_getBallsCount},
    {"getHatCount", l_joystick_getHatCount},
    {"getHat", l_joystick_getHat},
    {"getAxisCount", l_joystick_getNumAxes},
    {"getAxis", l_joystick_getAxis},
    {"getName", l_joystick_getName},
    {"isConnected", l_joystick_isConnected},
    {"isGamepad", l_joystick_isGamepad},
    {"isDown", l_joystick_isDown},
    {"getCount", l_joystick_getJoystickCount},
    {NULL, NULL}
};

void l_joystick_register(lua_State *state) {
    moduleData.luaState = state;
    l_tools_registerModule(state, "joystick", regFuncs);
}

#endif
