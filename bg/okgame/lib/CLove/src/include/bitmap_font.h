/*
#   clove
#
#   Copyright (C) 2017-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "imagedata.h"
#include "image.h"
#include "batch.h"
#include "quad.h"

typedef struct
{
    float offsetx;
    float offsety;
    uint32_t word;
    uint16_t index;
    graphics_Quad* quad;
} glyph_t;

typedef struct
{
    glyph_t* glyphs_t;
    uint16_t indexer_map_size;
    uint32_t allocated_glyphs;
    uint16_t glyph_width;
    uint16_t glyph_height;

    graphics_Batch* batches;
    image_ImageData* data;
    graphics_Image* image;
} graphics_BitmapFont;

void graphics_BitmapFont_new(graphics_BitmapFont* dst, char const* filename,
                             int max_size, char const* glyphs, float glyph_width, float glyph_height);

void graphics_BitmapFont_setGlyphOffsetX(graphics_BitmapFont *font, float off, char const* glyph);
void graphics_BitmapFont_setGlyphOffsetY(graphics_BitmapFont *font, float off, char const* glyph);
void graphics_BitmapFont_render(graphics_BitmapFont *font, char const* text,
                                int x, int y, float r, float sx, float sy, float ox, float oy, float kx, float ky);
void graphics_BitmapFont_setFilter(graphics_BitmapFont *font, graphics_Filter const* filter);
void graphics_BitmapFont_getFilter(graphics_BitmapFont *font, graphics_Filter *filter);
int graphics_BitmapFont_getWidth(graphics_BitmapFont *font, char const* line);
int graphics_BitmapFont_getWrap(graphics_BitmapFont *font, char const* line, int wraplimit, char **wrappedtext);
void graphics_BitmapFont_free(graphics_BitmapFont* dst);
