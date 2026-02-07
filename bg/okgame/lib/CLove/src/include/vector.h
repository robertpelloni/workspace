/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/CMath/cmath.h"

#define LOVE_PI 3.141592653589793238462643383279502884L
#define LOVE_PI2 (2 * LOVE_PI)

#define CLAMP(x, min, max) x >= max ? x = max : x <= min ? x = min : x

void normalizeInPlace(float *x, float *y);

void m4x4_newTransform3d(mat4x4 *out, vec3 pos, float angle, vec3 axis, vec3 scale,
                         float ox, float oy, float kx, float ky);
void m4x4_newTransform2d(mat4x4 *out, float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky);

void m4x4_translate(mat4x4 *inout, float x, float y, float z);

void m4x4_scalexyz(mat4x4 *inout, float x, float y, float z);
void m4x4_scale(mat4x4 *inout,float angle, float r_x, float r_y, float r_z, float x, float y, float z);

// FIXME: Just a note
// Missing in src/3rdparty/CMath/cmath.h
//void m4x4_shear2d(mat4x4 *inout, float x, float y);

void m3x3_newTransform2d(mat3x3 *out, float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky, float w, float h);

// Assumes that v is a 2d point (homogeneous coord == 1).
// This allows much faster multiplication
void m3x3_mulV2(vec2 *out, mat3x3 const* m, vec2 const* v);
