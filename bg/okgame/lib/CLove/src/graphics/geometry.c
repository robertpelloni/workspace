/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include <stdlib.h>
#include <math.h>

#include "../include/vector.h"
#include "../include/geometry.h"
#include "../include/graphics.h"
#include "../include/shader.h"
#include "../include/matrixstack.h"
#include "../include/vertex.h"

static struct {
    GLuint vao;
    GLuint dataVBO;
    GLuint dataIBO;
    uint32_t currentDataSize;
    uint32_t currentIndexSize;
    float *data;
    uint32_t *index;
    graphics_Shader plainColorShader;
    float lineWidth;
    graphics_Quad quad;
    mat4x4 tr;
} moduleData;

void graphics_geometry_init(void) {
    // Core profile requires a VAO for vertex attribute state.
    glGenVertexArrays(1, &moduleData.vao);
    glBindVertexArray(moduleData.vao);

    glGenBuffers(1, &moduleData.dataVBO);
    glBindBuffer(GL_ARRAY_BUFFER, moduleData.dataVBO);

    glGenBuffers(1, &moduleData.dataIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.dataIBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *) (4 * sizeof(GLfloat)));

    // Done configuring VAO state
    glBindVertexArray(0);

    graphics_Shader_new(&moduleData.plainColorShader, NULL,
                        "vec4 effect(vec4 color, Image texture, vec2 texture_coords, vec2 screen_cords ) {\n"
                        "  return color;\n"
                        "}\n");

    moduleData.lineWidth = 1.0f;
    moduleData.quad = (graphics_Quad){0.0f, 0.0f, 1.0f, 1.0f};

    moduleData.currentDataSize = 0;
    moduleData.currentIndexSize = 0;
}

void graphics_geometry_free() {
    glDeleteVertexArrays(1, &moduleData.vao);
    glDeleteBuffers(1, &moduleData.dataIBO);
    glDeleteBuffers(1, &moduleData.dataVBO);
    free(moduleData.data);
    free(moduleData.index);
    graphics_Shader_free(&moduleData.plainColorShader);
}

static void growBuffers(int vertices, int indices) {
    uint32_t datasize = vertices * 8 * sizeof(GLfloat);
    if (moduleData.currentDataSize < datasize) {
        free(moduleData.data);
        moduleData.data = (float *) malloc(datasize);
        moduleData.currentDataSize = datasize;
    }

    uint32_t indexsize = indices * sizeof(uint32_t);
    if (moduleData.currentIndexSize < indexsize) {
        free(moduleData.index);
        moduleData.index = (uint32_t *) malloc(indexsize);
        moduleData.currentIndexSize = indexsize;
    }
}

static void drawBufferSpecial(uint32_t indices,
                              int vertices,
                              float x, float y,
                              float r,
                              float w, float h,
                              float sx, float sy,
                              float ox, float oy, GLenum type) {
    glBindVertexArray(moduleData.vao);
    glBindBuffer(GL_ARRAY_BUFFER, moduleData.dataVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices * 8 * sizeof(GLfloat), moduleData.data, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.dataIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices * sizeof(uint32_t),
                 moduleData.index, GL_STREAM_DRAW);

    glLineWidth(moduleData.lineWidth);

    graphics_Shader *shader = graphics_getShader();
    graphics_setShader(&moduleData.plainColorShader);

    m4x4_newTransform2d(&moduleData.tr, x, y, r, sx, sy, ox, oy, 0.0f, 0.0f);

    graphics_drawArray(&moduleData.quad, &moduleData.tr, moduleData.dataIBO, indices,
                       type, GL_UNSIGNED_INT, graphics_getColor(), w, h);

    graphics_setShader(shader);

    glLineWidth(1.0f);

    glBindVertexArray(0);
}

static void drawBuffer(uint32_t indices, int vertices, GLenum type) {
    glBindVertexArray(moduleData.vao);
    glBindBuffer(GL_ARRAY_BUFFER, moduleData.dataVBO);
    glBufferData(GL_ARRAY_BUFFER, vertices * 8 * sizeof(GLfloat), moduleData.data, GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, moduleData.dataIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices * sizeof(uint32_t),
                 moduleData.index, GL_STREAM_DRAW);

    glLineWidth(moduleData.lineWidth);

    graphics_Shader *shader = graphics_getShader();
    graphics_setShader(&moduleData.plainColorShader);

    m4x4_newIdentity(&moduleData.tr);

    graphics_drawArray(&moduleData.quad, &moduleData.tr, moduleData.dataIBO, indices,
                       type, GL_UNSIGNED_INT, graphics_getColor(), 1.0f, 1.0f);

    graphics_setShader(shader);
    glLineWidth(1.0f);

    glBindVertexArray(0);
}

void graphics_geometry_lineCircle(float x, float y, float radius,
                                  uint32_t segments, float r, float sx, float sy, float ox, float oy) {
    growBuffers(segments + 1, segments + 2);

    float step = LOVE_PI2 / segments;
    float ang = 0;

    moduleData.index[0] = 1;
    moduleData.index[segments + 1] = 1;
    for (uint32_t i = 0; i < segments; ++i, ang -= step) {
        moduleData.data[8 * (i + 1) + 0] = sinf(ang) * radius;
        moduleData.data[8 * (i + 1) + 1] = cosf(ang) * radius;

        moduleData.data[8 * (i + 1) + 2] = 0.0f;
        moduleData.data[8 * (i + 1) + 3] = 0.0f;

        moduleData.data[8 * (i + 1) + 4] = 1.0f;
        moduleData.data[8 * (i + 1) + 5] = 1.0f;
        moduleData.data[8 * (i + 1) + 6] = 1.0f;
        moduleData.data[8 * (i + 1) + 7] = 1.0f;
        moduleData.index[i + 1] = i + 1;
    }

    drawBufferSpecial(segments + 2, segments + 1, x, y, r, 1, 1, sx, sy, ox, oy, GL_LINE_STRIP);
}

void graphics_geometry_fillCircle(float x, float y, float radius, uint32_t segments, float r, float sx, float sy,
                                  float ox, float oy) {
    growBuffers(segments + 1, segments + 2);

    float step = LOVE_PI2 / segments;
    float ang = 0;

    moduleData.data[0] = 1.0f;
    moduleData.data[1] = 1.0f;
    moduleData.data[2] = 0.0f;
    moduleData.data[3] = 0.0f;
    moduleData.data[4] = 1.0f;
    moduleData.data[5] = 1.0f;
    moduleData.data[6] = 1.0f;
    moduleData.data[7] = 1.0f;

    moduleData.index[0] = 0;
    moduleData.index[segments + 1] = 1;
    for (uint32_t i = 0; i < segments; ++i, ang -= step) {
        moduleData.data[8 * (i + 1) + 0] = sin(ang) * radius;
        moduleData.data[8 * (i + 1) + 1] = cos(ang) * radius;

        moduleData.data[8 * (i + 1) + 2] = 0.0f;
        moduleData.data[8 * (i + 1) + 3] = 0.0f;

        moduleData.data[8 * (i + 1) + 4] = 1.0f;
        moduleData.data[8 * (i + 1) + 5] = 1.0f;
        moduleData.data[8 * (i + 1) + 6] = 1.0f;
        moduleData.data[8 * (i + 1) + 7] = 1.0f;
        moduleData.index[i + 1] = i + 1;
    }

    drawBufferSpecial(segments + 2, segments + 1, x, y, r, 1, 1, sx, sy, ox, oy, GL_TRIANGLE_FAN);
}

void graphics_geometry_rectangle(bool filled,
                                 float x, float y,
                                 float w, float h,
                                 float rotation,
                                 float sx, float sy,
                                 float ox, float oy) {
    growBuffers(32, 6);

    bool special = rotation != 0.0f || sx != 1.0f || sy != 1.0f;

    /*
     * What is commented with 0,1,2,3 represent the declaration of the shape for this rectangle
     * the rest are texcoords(2 floats) and color(4 floats)
     */

    if (!special) {
        moduleData.data[0] = x + w * sx; //0
        moduleData.data[1] = y;

        moduleData.data[8] = x; //1
        moduleData.data[9] = y;

        moduleData.data[16] = x; //2
        moduleData.data[17] = y + h * sy;

        moduleData.data[24] = x + w * sx; //3
        moduleData.data[25] = y + h * sy;
    } else {
        /* For more info see image.c -> imageData[]
         * these are vertices */
        moduleData.data[0] = 0.0f; //0
        moduleData.data[1] = 0.0f;

        moduleData.data[8] = 1.0f; // 1
        moduleData.data[9] = 0.0f;

        moduleData.data[16] = 1.0f; // 2
        moduleData.data[17] = 1.0f;

        moduleData.data[24] = 0.0f; // 3
        moduleData.data[25] = 1.0f;
    }

    //these grouped by 2 are text coords
    moduleData.data[2] = 0.0f;
    moduleData.data[3] = 0.0f;

    //these grouped by 4 are colors
    moduleData.data[4] = 1.0f;
    moduleData.data[5] = 1.0f;
    moduleData.data[6] = 1.0f;
    moduleData.data[7] = 1.0f;

    moduleData.data[10] = 1.0f;
    moduleData.data[11] = 0.0f;

    moduleData.data[12] = 1.0f;
    moduleData.data[13] = 1.0f;
    moduleData.data[14] = 1.0f;
    moduleData.data[15] = 1.0f;

    moduleData.data[18] = 0.0f;
    moduleData.data[19] = 1.0f;

    moduleData.data[20] = 1.0f;
    moduleData.data[21] = 1.0f;
    moduleData.data[22] = 1.0f;
    moduleData.data[23] = 1.0f;

    moduleData.data[26] = 1.0f;
    moduleData.data[27] = 1.0f;
    moduleData.data[28] = 1.0f;
    moduleData.data[29] = 1.0f;
    moduleData.data[30] = 1.0f;
    moduleData.data[31] = 1.0f;

    if (filled) {
        moduleData.index[0] = 0;
        moduleData.index[1] = 1;
        moduleData.index[2] = 2;
        moduleData.index[3] = 0;
        moduleData.index[4] = 2;
        moduleData.index[5] = 3;

        if (special)
            drawBufferSpecial(6, 32, x, y, rotation, w, h, sx, sy, ox, oy, GL_TRIANGLES);
        else
            drawBuffer(6, 32, GL_TRIANGLES);
    } else {
        moduleData.index[0] = 0;
        moduleData.index[1] = 1;
        moduleData.index[2] = 2;
        moduleData.index[3] = 3;
        moduleData.index[4] = 0;
        moduleData.index[5] = 1;

        if (special)
            drawBufferSpecial(6, 32, x, y, rotation, w, h, sx, sy, ox, oy, GL_LINE_STRIP);
        else
            drawBuffer(6, 32, GL_LINE_STRIP);
    }
}

void graphics_geometry_points(float *points, uint32_t count) {
    growBuffers(count, count);

    for (uint32_t i = 0; i < count; i++) {
        moduleData.data[8 * i + 0] = points[2 * i];
        moduleData.data[8 * i + 1] = points[2 * i + 1];
        moduleData.data[8 * i + 2] = 0.0f;
        moduleData.data[8 * i + 3] = 0.0f;
        moduleData.data[8 * i + 4] = 1.0f;
        moduleData.data[8 * i + 5] = 1.0f;
        moduleData.data[8 * i + 6] = 1.0f;
        moduleData.data[8 * i + 7] = 1.0f;

        moduleData.index[i] = i;
    }

    drawBuffer(count, count, GL_POINTS);
}

void graphics_geometry_line(float *points, uint32_t count) {
    graphics_geometry_polygon(false, points, count);
}

void graphics_geometry_polygon(bool filled, float *vertices, uint32_t count) {
    growBuffers(count, count);

    for (uint32_t i = 0; i < count; i++) {
        moduleData.data[8 * i + 0] = vertices[2 * i];
        moduleData.data[8 * i + 1] = vertices[2 * i + 1];
        moduleData.data[8 * i + 2] = 0.0f;
        moduleData.data[8 * i + 3] = 0.0f;
        moduleData.data[8 * i + 4] = 1.0f;
        moduleData.data[8 * i + 5] = 1.0f;
        moduleData.data[8 * i + 6] = 1.0f;
        moduleData.data[8 * i + 7] = 1.0f;
        moduleData.index[i] = i;
    }

    drawBuffer(count, count, filled ? GL_TRIANGLE_STRIP : GL_LINE_STRIP);
}


void graphics_geometry_setLineWidth(float width) {
    moduleData.lineWidth = width;
}

float graphics_geometry_getLineWidth() {
    return moduleData.lineWidth;
}
