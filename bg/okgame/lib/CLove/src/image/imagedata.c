/*
#   clove
#
#   Copyright (C) 2016-2025 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.c"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../include/stb_image_write.h"

#include "../include/imagedata.h"

void image_ImageData_new_with_filename(image_ImageData *dst, char const *filename) {
  int n;
  dst->surface = stbi_load(filename, &dst->w, &dst->h, &n, STBI_default);
  dst->c = n;
  dst->path = filename;

  if (!dst->surface) {
    clove_error("%s %s\n", "Error: Could not open image: ", filename);
    return;
  }
  dst->pixels = (pixel *) dst->surface;
}

void image_ImageData_new_with_size(image_ImageData *dst, int width, int height, int num_channels) {
  dst->surface = malloc(sizeof(unsigned char) * width * height * num_channels);
  dst->w = width;
  dst->h = height;
  dst->c = num_channels;
  dst->path = "";
  memset(dst->surface, 255, sizeof(unsigned char) * width * height * num_channels);
  dst->pixels = (pixel *) dst->surface;
}

void image_ImageData_new_with_surface(image_ImageData *dst, unsigned char *surface,
                                      unsigned int width, unsigned int height, unsigned int num_channels) {
  size_t size = sizeof(unsigned char) * width * height * num_channels;
  dst->surface = malloc(size);
  memcpy(dst->surface, surface, size);
  dst->w = width;
  dst->h = height;
  dst->c = num_channels;
  dst->path = "";
  dst->pixels = (pixel *) dst->surface;
}

const char *image_ImageData_getPath(image_ImageData *dst) {
  return dst->path;
}

int image_ImageData_getChannels(image_ImageData *dst) {
  return dst->c;
}

pixel image_ImageData_getPixel(image_ImageData *dst, int x, int y) {
  return dst->pixels[y * dst->w + x];
}

int image_ImageData_setPixel(image_ImageData *dst, int x, int y, pixel p) {
  pixel *pixels = (pixel *) dst->surface;
  pixels[y * dst->w + x] = p;

  dst->pixels = (pixel *) dst->surface;
  dst->pixels[y * dst->w + x] = p;

  return 1;
}

int image_ImageData_save(image_ImageData *dst, const char *format, const char *filename) {
  int succeded = 0;
  if (strncmp(format, "png", 3) == 0)
    succeded = stbi_write_png(filename, dst->w, dst->h, dst->c, (const void *) dst->surface, 0);
  else if (strncmp(format, "bmp", 3) == 0)
    succeded = stbi_write_bmp(filename, dst->w, dst->h, dst->c, (const void *) dst->surface);
  else if (strncmp(format, "tga", 3) == 0)
    succeded = stbi_write_tga(filename, dst->w, dst->h, dst->c, (const void *) dst->surface);
  else if (strncmp(format, "hdr", 3) == 0)
    succeded = stbi_write_hdr(filename, dst->w, dst->h, dst->c, (const float *) dst->surface);
  else
    clove_error("%s %s %s \n", "Error, format:", format,
                " is not available.Only png,bmp,tga and hdr image formats are possible");
  if (succeded != 0)
    return 1;
  else {
    clove_error("%s %s\n", "Error: failed to save imageData: ", filename);
    return 0;
  }
}

void image_ImageData_setSurface(image_ImageData *dst, unsigned char *data) {
  if (dst->surface) {
    stbi_image_free(dst->surface);
  }
  dst->surface = data;
  dst->pixels = (pixel *) dst->surface;
}

unsigned char *image_ImageData_getSurface(image_ImageData *dst) {
  return dst->surface;
}

int image_ImageData_getWidth(image_ImageData *dst) {
  return dst->w;
}

int image_ImageData_getHeight(image_ImageData *dst) {
  return dst->h;
}

const char *image_error(void) {
  return stbi_failure_reason();
}

void image_ImageData_free(image_ImageData *data) {
  stbi_image_free(data->surface);
  data->surface = NULL;
  data->pixels = NULL;
}

void image_init(void) {
}

