/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once


#ifdef USE_FH

#include "../3rdparty/FH/src/fh.h"

#include "../include/joystick.h"

void fh_joystick_register(struct fh_program *prog);

void fh_joystick_pressed(int id, int button);
void fh_joystick_released(int id, int button);

#endif
