/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "vector.h"

void matrixstack_init(void);
int matrixstack_push(void);
int matrixstack_pop(void);
void matrixstack_origin(void);
mat4x4 * matrixstack_head(void);
void matrixstack_translate(float x, float y, float z);
void matrixstack_scale(float x, float y, float z);
void matrixstack_origin(void);
void matrixstack_rotate_3d(float r, float x, float y, float z);
void matrixstack_rotate(float a);
void matrixstack_multiply(mat4x4 const* matrix);
void matrixstack_shear_2d(float x, float y);
