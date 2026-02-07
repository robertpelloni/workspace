/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "graphics_mesh.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/mesh.h"

#include "image.h"

static struct {
    graphics_Vertex* vertices;
    uint32_t verticesSize;
    unsigned int* indices;
    int indicesSize;
} moduleData;

static void feedVertices(uint32_t size) {
    if (moduleData.verticesSize <  size) {
        free(moduleData.vertices);
        moduleData.vertices = malloc(size);
        moduleData.verticesSize = size;
    }
}

static void feedIndices(int size) {
    if (moduleData.indicesSize <  size) {
        free(moduleData.indices);
        moduleData.indices = malloc(size);
        moduleData.indicesSize = size;
    }
}

static long readVertices(struct fh_program *prog, struct fh_value *args, struct fh_array *arr) {
    feedVertices(arr->len * sizeof(graphics_Vertex));

    for (uint32_t i = 0; i < arr->len; i++) {
        if (!fh_is_array(&arr->items[i]))
            return fh_set_error(prog, "Expected array of vertices");

        struct fh_array *elm_arr = GET_VAL_ARRAY(&arr->items[i]);

        for (int j = 0; j < 3; j++) {
            if (!fh_is_number(&elm_arr->items[j]))
                return fh_set_error(prog, "Expected number at index %d", j);
        }

        moduleData.vertices[i].pos.x = (float)fh_get_number(&elm_arr->items[0]);
        moduleData.vertices[i].pos.y = (float)fh_get_number(&elm_arr->items[1]);

        moduleData.vertices[i].uv.x = (float)fh_get_number(&elm_arr->items[2]);
        moduleData.vertices[i].uv.y = (float)fh_get_number(&elm_arr->items[3]);

        moduleData.vertices[i].color.x = (float)fh_optnumber(elm_arr->items, elm_arr->len, 4, 255.0) / 255.0f;
        moduleData.vertices[i].color.y = (float)fh_optnumber(elm_arr->items, elm_arr->len, 5, 255.0) / 255.0f;
        moduleData.vertices[i].color.z = (float)fh_optnumber(elm_arr->items, elm_arr->len, 6, 255.0) / 255.0f;
        moduleData.vertices[i].color.w = (float)fh_optnumber(elm_arr->items, elm_arr->len, 7, 255.0) / 255.0f;
    }
    return arr->len;
}

static long readIndices(struct fh_program *prog, struct fh_value *args, struct fh_array *arr) {
    feedIndices(arr->len * sizeof(unsigned int));
    unsigned int *indices = moduleData.indices;

    for (uint32_t i = 0; i < arr->len; i++) {
        if (!fh_is_number(&arr->items[i]))
            return fh_set_error(prog, "Expected indice as number");

        indices[i] = (unsigned int)fh_get_number(&arr->items[i]);
    }

    return arr->len;
}

static fh_c_obj_gc_callback on_gc(graphics_Mesh *mesh) {
    graphics_Mesh_free(mesh);
    free(mesh);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_graphics_newMesh(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_array(&args[0]) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected array of vertices and array of indices");

    struct fh_array *arrVertices = GET_VAL_ARRAY(&args[0]);
    int vertexCount = readVertices(prog, args, arrVertices);

    struct fh_array *arrIndices = GET_VAL_ARRAY(&args[1]);

    readIndices(prog, args, arrIndices);

    const char *mode_str = fh_optstring(args, n_args, 2, "fan");
    graphics_MeshDrawMode mode = graphics_MeshDrawMode_fan;
    if (strcmp(mode_str, "fan") == 0) {
        mode = graphics_MeshDrawMode_fan;
    } else if (strcmp(mode_str, "strip") == 0) {
        mode = graphics_MeshDrawMode_strip;
    } else if (strcmp(mode_str, "triangles") == 0) {
        mode = graphics_MeshDrawMode_triangles;
    } else if (strcmp(mode_str, "points") == 0) {
        mode = graphics_MeshDrawMode_points;
    } else {
        return fh_set_error(prog, "Cannot handle mesh draw mode '%s'\n", mode_str);
    }
    graphics_Mesh *mesh = malloc(sizeof(graphics_Mesh));
    graphics_Mesh_new(mesh, vertexCount, (graphics_Vertex*)moduleData.vertices, arrIndices->len, moduleData.indices, mode);

    fh_c_obj_gc_callback *callback = on_gc;

    *ret = fh_new_c_obj(prog, mesh, callback, FH_GRAPHICS_MESH);
    return 0;
}

static int fn_love_mesh_setTexture(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    // We also enable the user to pass "null" as texture param which results in having a blank mesh
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_MESH))
        return fh_set_error(prog, "Expected mesh");
    if (!fh_is_c_obj_of_type(&args[1], FH_IMAGE_TYPE) && !fh_is_null(&args[1]))
        return fh_set_error(prog, "Expected image or null");

    graphics_Mesh *mesh = fh_get_c_obj_value(&args[0]);

    if (!fh_is_null(&args[1])) {
        fh_image_t *image = fh_get_c_obj_value(&args[1]);
        graphics_Mesh_setTexture(mesh, image->img);
    } else {
        graphics_Mesh_setTexture(mesh, NULL);
    }

    *ret = fh_new_null();
    return 0;
}

static int fn_love_mesh_setVertices(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_MESH) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected mesh and array of vertices");
    UNUSED(n_args);

    graphics_Mesh *mesh = fh_get_c_obj_value(&args[0]);
    struct fh_array *arr = GET_VAL_ARRAY(&args[1]);
    int vertexCount = readVertices(prog, args, arr);

    graphics_Mesh_setVertices(mesh, moduleData.vertices, vertexCount);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_mesh_setIndices(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_MESH) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected mesh and array of vertices");
    UNUSED(n_args);

    graphics_Mesh *mesh = fh_get_c_obj_value(&args[0]);
    struct fh_array *arr = GET_VAL_ARRAY(&args[1]);

    int indexCount = readIndices(prog, args, arr);

    graphics_Mesh_setIndices(mesh, moduleData.indices, indexCount);

    *ret = fh_new_null();
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newMesh),
    DEF_FN(love_mesh_setVertices),
    DEF_FN(love_mesh_setIndices),
    DEF_FN(love_mesh_setTexture),
};

void fh_graphics_mesh_register(struct fh_program *prog) {
    moduleData.indicesSize = 0;
    moduleData.verticesSize = 0;
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
