
/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#pragma once

#include "../3rdparty/SDL2/include/SDL.h"
#include "stdbool.h"

typedef struct {
    SDL_Joystick *joystick;
    SDL_JoystickID id;
    SDL_GameController *controller;
} joystick_Joystick;

// events
float joystick_getAxis(joystick_Joystick *joystick, int axis);

void joystick_buttonDown(int id, int button, int state);

void joystick_buttonUp(int id, int button, int state);

bool joystick_isDown(joystick_Joystick *joystick, int button);

// common functions
void joystick_init();

joystick_Joystick *joystick_get(SDL_JoystickID id);

int joystick_getCount();

int joystick_getNumAxes(joystick_Joystick *joystick);

int joystick_getNumButtons(joystick_Joystick *joystick);

int joystick_getNumBalls(joystick_Joystick *joystick);

const char *joystick_getName(joystick_Joystick *joystick);

bool joystick_isConnected(joystick_Joystick *joystick);

bool joystick_isGamepad(joystick_Joystick *joystick);

int joystick_getHatCount(joystick_Joystick *joystick);

int joystick_getHat(joystick_Joystick *joystick, int hat);

float joystick_getGamepadAxis(joystick_Joystick *joystick, int axis);

void joystick_added(int id);

void joystick_close();

void joystick_remove(int id);


int joystick_convert_str_to_button(const char *v);

const char *joystick_convert_button_to_str(int v);
