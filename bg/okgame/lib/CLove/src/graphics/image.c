/*
#   clove
#
#   Copyright (C) 2016-2025 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "../include/image.h"
#include "../include/imagedata.h"
#include "../include/graphics.h"
#include "../include/vertex.h"
#include "../include/shader.h"

static graphics_Vertex const imageData[] = {
    {{0.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{1.0f, 0.0f}, {1.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{0.0f, 1.0f}, {0.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}},
    {{1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
};

static unsigned char const imageIndices[] = {0, 1, 2, 3};

void graphics_image_init(void) {
}

static const graphics_Wrap defaultWrap = {
    .verMode = graphics_WrapMode_clamp,
    .horMode = graphics_WrapMode_clamp
};

static const graphics_Filter defaultFilter = {
    .maxAnisotropy = 1.0f,
    .mipmapLodBias = 1.0f,
    .minMode = graphics_FilterMode_linear,
    .magMode = graphics_FilterMode_linear,
    .mipmapMode = graphics_FilterMode_none
};

void graphics_Image_new_with_ImageData(graphics_Image *dst, image_ImageData *data) {
    dst->texID = 0;
    dst->path = NULL;
    dst->width = 0;
    dst->height = 0;

    glGenVertexArrays(1, &dst->vao);
    glBindVertexArray(dst->vao);

    glGenBuffers(1, &dst->vbo);
    glGenBuffers(1, &dst->ibo);

    glBindBuffer(GL_ARRAY_BUFFER, dst->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(imageData), imageData, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dst->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(imageIndices), imageIndices, GL_STATIC_DRAW);

    // layout: pos(2), uv(2), color(4)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
                          (void *) offsetof(graphics_Vertex, pos));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
                          (void *) offsetof(graphics_Vertex, uv));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(graphics_Vertex),
                          (void *) offsetof(graphics_Vertex, color));

    glBindVertexArray(0);

    graphics_Image_refresh(dst, data);
}

void graphics_Image_refresh(graphics_Image *img, image_ImageData const *data) {
    if (img->texID == 0) glGenTextures(1, &img->texID);
    glBindTexture(GL_TEXTURE_2D, img->texID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    img->width = data->w;
    img->height = data->h;
    img->path = data->path;

    GLenum format;
    GLint internalFormat;

#ifndef CLOVE_WEB
    switch (image_ImageData_getChannels((image_ImageData *) data)) {
        case 1: // alpha-only în engine
            format = GL_RED;
            internalFormat = GL_R8;

            // RGB = 1, A = R
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_ONE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_ONE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_ONE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_RED);
            break;

        case 2: // lum + alpha (R=lum, G=alpha)
            format = GL_RG;
            internalFormat = GL_RG8;

            // RGB = R, A = G
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_RED);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_RED);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_GREEN);
            break;

        case 3:
            format = GL_RGB;
            internalFormat = GL_RGB8;

            // default swizzle
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ONE);
            break;

        default: // 4
            format = GL_RGBA;
            internalFormat = GL_RGBA8;

            // default swizzle
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_R, GL_RED);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_G, GL_GREEN);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_B, GL_BLUE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_A, GL_ALPHA);
            break;
    }
#else
    switch (image_ImageData_getChannels((image_ImageData *) data)) {
        case 1: // alpha only
            format = GL_LUMINANCE;
            internalFormat = GL_LUMINANCE;
            break;
        case 2: // greyscale
            format = GL_LUMINANCE_ALPHA;
            internalFormat = GL_LUMINANCE_ALPHA;
            break;
        case 3:
            format = GL_RGB;
            internalFormat = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            internalFormat = GL_RGBA;
            break;

        default:
            format = GL_RGBA;
            internalFormat = GL_RGBA;
            break;
    }
#endif
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, data->w, data->h, 0, format, GL_UNSIGNED_BYTE, data->surface);

    graphics_Image_setFilter(img, &defaultFilter);
    graphics_Image_setWrap(img, &defaultWrap);
}

void graphics_Image_free(graphics_Image *obj) {
    glDeleteTextures(1, &obj->texID);
    glDeleteBuffers(1, &obj->ibo);
    glDeleteBuffers(1, &obj->vbo);
    glDeleteVertexArrays(1, &obj->vao);
}

void graphics_Image_setFilter(graphics_Image *img, graphics_Filter const *filter) {
    graphics_Texture_setFilter(img->texID, filter);
}

void graphics_Image_getFilter(graphics_Image *img, graphics_Filter *filter) {
    graphics_Texture_getFilter(img->texID, filter);
}

void graphics_Image_setWrap(graphics_Image *img, graphics_Wrap const *wrap) {
    glBindTexture(GL_TEXTURE_2D, img->texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap->horMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap->verMode);
}

void graphics_Image_getWrap(graphics_Image *img, graphics_Wrap *wrap) {
    glBindTexture(GL_TEXTURE_2D, img->texID);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int *) &wrap->horMode);
    glGetTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int *) &wrap->verMode);
}

void graphics_Image_draw(graphics_Image *image, graphics_Quad const *quad,
                         float x, float y, float r, float sx, float sy,
                         float ox, float oy, float kx, float ky) {
    glBindVertexArray(image->vao);
    glBindBuffer(GL_ARRAY_BUFFER, image->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, image->ibo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(imageData), imageData, GL_STATIC_DRAW);

    m4x4_newTransform2d(&image->tr2d, x, y, r, sx, sy, ox, oy, kx, ky);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, image->texID);

    graphics_drawArray(quad, &image->tr2d, image->ibo, 4, GL_TRIANGLE_STRIP, GL_UNSIGNED_BYTE,
                       graphics_getColor(), image->width * quad->w, image->height * quad->h);
    glBindVertexArray(0);
}
