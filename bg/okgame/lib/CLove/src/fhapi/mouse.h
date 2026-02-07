/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_FH
#include "../3rdparty/FH/src/fh.h"

void fh_mouse_register(struct fh_program* prog);
void fh_mouse_pressed(int x, int y, int button);
void fh_mouse_released(int x, int y, int button);
void fh_mouse_wheelmoved(int y);
#endif
