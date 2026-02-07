/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/FH/src/fh.h"

#include "../include/shader.h"

#define FH_GRAPHICS_SHADER 8

typedef struct {
  graphics_Shader shader;
  int referencedTextures;
} fh_graphics_Shader;

void fh_graphics_shader_register(struct fh_program *prog);
