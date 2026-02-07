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

#include "../include/imagedata.h"
#include "../include/image.h"

#define FH_IMAGE_TYPE 9
#define FH_IMAGE_DATA_TYPE 11

typedef struct {
    image_ImageData *data;
    graphics_Image *img;
} fh_image_t;

void fh_image_register(struct fh_program *prog);
