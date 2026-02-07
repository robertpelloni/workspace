/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include <stdlib.h>
#include <stdbool.h>

#include "include/utils.h"

#include "include/joystick.h"

#ifdef USE_LUA
#include "luaapi/joystick.h"
#endif

static struct {
    joystick_Joystick* list;
    int joystick_count;
} moduleData;

joystick_Joystick* joystick_get(SDL_JoystickID id) {
    for (int i = 0; i < moduleData.joystick_count; i++) {
        joystick_Joystick* js = &moduleData.list[i];
        if (js->id == id)
            return js;
    }
    clove_error("CLove error, returning null joystick instance \n");
    return 0;
}

static joystick_Joystick* openJoystick(int index) {
    moduleData.list->joystick = SDL_JoystickOpen(index);

    if (moduleData.list->joystick == NULL) {
        clove_error("Joystick error: %s \n", SDL_GetError());
        return NULL;
    }
    moduleData.list->id = SDL_JoystickInstanceID(moduleData.list->joystick);

    if (SDL_IsGameController(index))
        moduleData.list->controller = SDL_GameControllerOpen(index);
    else
        moduleData.list->controller = 0;

    return moduleData.list;
}

void joystick_init() {
    moduleData.list = realloc(moduleData.list, sizeof(joystick_Joystick) * 1);
    if(SDL_InitSubSystem(SDL_INIT_JOYSTICK) != 0) {
        clove_error("Joystick error %s \n", SDL_GetError());
        return;
    }

    if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) != 0) {
        clove_error("Joystick error %s \n", SDL_GetError());
        return;
    }
    moduleData.joystick_count = SDL_NumJoysticks();
}

void joystick_added(int id) {
    joystick_Joystick* js = openJoystick(id);
}

// Close all devices when clove quits
void joystick_close() {
    for (int i = 0; i < moduleData.joystick_count; i++) {
        joystick_Joystick* js = joystick_get(i);
        if (SDL_JoystickGetAttached(js->joystick))
            SDL_JoystickClose(js->joystick);
        free(js);
    }
}
// Close a certain device when it has been disconected from machine
void joystick_remove(int id) {
    joystick_Joystick* js = joystick_get(id);
    SDL_JoystickClose(js->joystick);
}

float joystick_getAxis(joystick_Joystick* joystick, int axis) {
    int16_t val = SDL_JoystickGetAxis(joystick->joystick, axis);
    return val / 32767.0f;
}

bool joystick_isDown(joystick_Joystick* joystick, int button) {
    return SDL_JoystickGetButton(joystick->joystick, button);
}

void joystick_buttonDown(int id, int button, int state) {
#ifdef USE_LUA
    l_joystick_pressed(id, button);
#endif
}

void joystick_buttonUp(int id, int button, int state) {
#ifdef USE_LUA
    l_joystick_released(id, button);
#endif
}

int joystick_getCount() {
    return moduleData.joystick_count;
}

int joystick_getNumAxes(joystick_Joystick* joystick) {
    return SDL_JoystickNumAxes(joystick->joystick);
}

int joystick_getNumButtons(joystick_Joystick* joystick) {
    return SDL_JoystickNumButtons(joystick->joystick);
}

int joystick_getNumBalls(joystick_Joystick* joystick) {
    return SDL_JoystickNumBalls(joystick->joystick);
}

const char* joystick_getName(joystick_Joystick* joystick) {
    return SDL_JoystickNameForIndex(joystick->id);
}

bool joystick_isConnected(joystick_Joystick* joystick) {
    return SDL_JoystickGetAttached(joystick->joystick);
}

bool joystick_isGamepad(joystick_Joystick* joystick) {
    return joystick->controller != 0;
}

int joystick_getHatCount(joystick_Joystick* joystick) {
    return SDL_JoystickNumHats(joystick->joystick);
}

int joystick_getHat(joystick_Joystick* joystick, int hat) {
    return SDL_JoystickGetHat(joystick->joystick, hat);
}

float joystick_getGamepadAxis(joystick_Joystick* joystick, int axis) {
    return SDL_GameControllerGetAxis(joystick->controller, (SDL_GameControllerAxis) axis) / 32767.0f;
}


int joystick_convert_str_to_button(const char* v) {
    if (strcmp("a", v) == 0)
        return SDL_CONTROLLER_BUTTON_A;
    else if (strcmp("b", v) == 0)
        return SDL_CONTROLLER_BUTTON_B;
    else if (strcmp("x", v) == 0)
        return SDL_CONTROLLER_BUTTON_X;
    else if (strcmp("y", v) == 0)
        return SDL_CONTROLLER_BUTTON_Y;
    else if (strcmp("back", v) == 0)
        return SDL_CONTROLLER_BUTTON_BACK;
    else if (strcmp("guide", v) == 0)
        return SDL_CONTROLLER_BUTTON_GUIDE;
    else if (strcmp("start", v) == 0)
        return SDL_CONTROLLER_BUTTON_START;
    else if (strcmp("leftstick", v) == 0)
        return SDL_CONTROLLER_BUTTON_LEFTSTICK;
    else if (strcmp("rightstick", v) == 0)
        return SDL_CONTROLLER_BUTTON_RIGHTSTICK;
    else if (strcmp("leftshoulder", v) == 0)
        return SDL_CONTROLLER_BUTTON_LEFTSHOULDER;
    else if (strcmp("rightshoulder", v) == 0)
        return SDL_CONTROLLER_BUTTON_RIGHTSHOULDER;
    else if (strcmp("dpup", v) == 0)
        return SDL_CONTROLLER_BUTTON_DPAD_UP;
    else if (strcmp("dpdown", v) == 0)
        return SDL_CONTROLLER_BUTTON_DPAD_DOWN;
    else if (strcmp("dpleft", v) == 0)
        return SDL_CONTROLLER_BUTTON_DPAD_LEFT;
    else if (strcmp("dpright", v) == 0)
        return SDL_CONTROLLER_BUTTON_DPAD_RIGHT;

    clove_error("Error: %s is not a valid joystick button!\n", v);
    return 0;
}

const char* joystick_convert_button_to_str(int v) {
    if (v == SDL_CONTROLLER_BUTTON_A)
        return "a";
     else if (v == SDL_CONTROLLER_BUTTON_B)
        return "b";
     else if (v == SDL_CONTROLLER_BUTTON_X)
        return "x";
     else if (v == SDL_CONTROLLER_BUTTON_Y)
        return "y";
     else if (v == SDL_CONTROLLER_BUTTON_BACK)
        return "back";
     else if (v == SDL_CONTROLLER_BUTTON_GUIDE)
        return "guide";
     else if (v == SDL_CONTROLLER_BUTTON_START)
        return "start";
     else if (v == SDL_CONTROLLER_BUTTON_LEFTSTICK)
        return "leftstick";
     else if (v == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
        return "rightstick";
     else if (v == SDL_CONTROLLER_BUTTON_LEFTSHOULDER)
        return "leftshoulder";
     else if (v == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)
        return "rightshoulder";
     else if (v == SDL_CONTROLLER_BUTTON_DPAD_UP)
        return "dpup";
     else if (v == SDL_CONTROLLER_BUTTON_DPAD_DOWN)
        return "dpdown";
     else if (v == SDL_CONTROLLER_BUTTON_DPAD_LEFT)
        return "dpleft";
     else if (v == SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
        return "dpright";

    clove_error("Error: %d is not a valid joystick button!\n", v);
    return "";

}

