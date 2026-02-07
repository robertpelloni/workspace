/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "imagedata.h"
#include "gl.h"
#include "vector.h"
#include "quad.h"
#include "gltools.h"

typedef enum {
  graphics_WrapMode_clamp = GL_CLAMP_TO_EDGE,
  graphics_WrapMode_repeat = GL_REPEAT
} graphics_WrapMode;


typedef struct {
  graphics_WrapMode verMode;
  graphics_WrapMode horMode;
} graphics_Wrap;


typedef struct {
  unsigned int texID;
  unsigned int vbo;
  unsigned int ibo;
  GLuint vao;
  int width;
  int height;
  //Used to store the path to loaded image. May return null.
  const char *path;
  mat4x4 tr2d;
} graphics_Image;


void graphics_image_init(void);

void graphics_Image_new_with_ImageData(graphics_Image *dst, image_ImageData *data);

void graphics_Image_free(graphics_Image *obj);

void graphics_Image_setFilter(graphics_Image *img, graphics_Filter const *filter);

void graphics_Image_getFilter(graphics_Image *img, graphics_Filter *filter);

void graphics_Image_setWrap(graphics_Image *img, graphics_Wrap const *wrap);

void graphics_Image_getWrap(graphics_Image *img, graphics_Wrap *wrap);

void graphics_Image_refresh(graphics_Image *img, image_ImageData const *data);

void graphics_Image_draw(graphics_Image *image, graphics_Quad const *quad, float x, float y, float r, float sx,
                         float sy, float ox, float oy, float kx, float ky);
