/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "graphics_geometry.h"
#include "tools.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/geometry.h"

static int fn_love_geometry_circle(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args < 4) {
        return fh_set_error(prog, "Expected at least 4 arguments, got %d", n_args);
    }

    const char* type = fh_get_string(&args[0]);
    double x = fh_get_number(&args[1]);
    double y = fh_get_number(&args[2]);
    double radius = fh_get_number(&args[3]);
    double segments = fh_optnumber(args, n_args, 4, 12);
    double rotation = fh_optnumber(args, n_args, 5, 0);
    double sx = fh_optnumber(args, n_args, 6, 1);
    double sy = fh_optnumber(args, n_args, 7, sx);
    double ox = fh_optnumber(args, n_args, 8, 0);
    double oy = fh_optnumber(args, n_args, 9, ox);

    if (strcmp(type, "line") == 0)
        graphics_geometry_lineCircle(x, y, radius, segments, rotation, sx, sy, ox, oy);
    else if(strcmp(type, "fill") == 0)
        graphics_geometry_fillCircle(x, y, radius, segments, rotation, sx, sy, ox, oy);
    else {
        return fh_set_error(prog, "Expected 'line' or 'fill' as input type!\n");
    }
    *ret = fh_new_null();
    return 0;
}

static int fn_love_geometry_rectangle(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args < 4) {
        return fh_set_error(prog, "Expected at least 5 arguments, got %d", n_args);
    }

    const char* type = fh_get_string(&args[0]);
    double x = fh_get_number(&args[1]);
    double y = fh_get_number(&args[2]);
    double w = fh_get_number(&args[3]);
    float h = fh_optnumber(args, n_args, 4, w);
    float rotation = fh_optnumber(args, n_args, 5, 0);
    float sx = fh_optnumber(args, n_args, 6, 1);
    float sy = fh_optnumber(args, n_args, 7, sx);
    float ox = fh_optnumber(args, n_args, 8, 0);
    float oy = fh_optnumber(args, n_args, 9, ox);

    if (strcmp(type, "line") == 0)
        graphics_geometry_rectangle(false, x, y, w, h, rotation, sx, sy, ox, oy);
    else if(strcmp(type, "fill") == 0)
        graphics_geometry_rectangle(true, x, y, w, h, rotation, sx, sy, ox, oy);
    else {
        return fh_set_error(prog, "Expected 'line' or 'fill' as input type!");
    }
    *ret = fh_new_null();
    return 0;
}

static int fn_love_geometry_points(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1) {
        return fh_set_error(prog, "Expected 1 argument for love_geometry_points");
    }

    struct fh_value *arr = &args[0];
    int len = fh_get_array_len(arr);
    float *vertices = malloc(sizeof(float)*len);

    struct fh_array *a = GET_VAL_ARRAY(arr);
    for (int i = 0; i < len; i++) {
        if (a->items[i].type != FH_VAL_FLOAT) {
            free (vertices);
            return fh_set_error(prog, "Expected index %d in array to be of type number, got %s", i, fh_type_to_str(prog, a->items[i].type));
        }
        vertices[i] = (float)a->items[i].data.num;
    }

    graphics_geometry_points(vertices, len * 0.5);
    *ret = fh_new_null();
    free(vertices);
    return 0;
}

static int fn_love_geometry_line(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1) {
        return fh_set_error(prog, "Expected 1 argument for love_geometry_line");
    }

    struct fh_value *arr = &args[0];
    int len = fh_get_array_len(arr);
    float *vertices = malloc(sizeof(float)*len);

    struct fh_array *a = GET_VAL_ARRAY(arr);
    for (int i = 0; i < len; i++) {
        if (a->items[i].type != FH_VAL_FLOAT) {
            free (vertices);
            return fh_set_error(prog, "Expected index %d in array to be of type number, got %s", i, fh_type_to_str(prog, a->items[i].type));
        }
        vertices[i] = (float)a->items[i].data.num;
    }

    graphics_geometry_line(vertices, len * 0.5f);
    *ret = fh_new_null();
    free(vertices);
    return 0;
}

static int fn_love_geometry_polygon(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_string(&args[0]) || !fh_is_array(&args[1])) {
        return fh_set_error(prog, "Expected 2 arguments, string and array, for love_geometry_polygon");
    }

    const char *filled = fh_get_string(&args[0]);

    struct fh_value *arr = &args[1];
    int len = fh_get_array_len(arr);
    float *vertices = malloc(sizeof(float)*len);

    struct fh_array *a = GET_VAL_ARRAY(arr);
    for (int i = 0; i < len; i++) {
        if (a->items[i].type != FH_VAL_FLOAT) {
            free (vertices);
            return fh_set_error(prog, "Expected index %d in array to be of type number, got %s", i, fh_type_to_str(prog, a->items[i].type));
        }
        vertices[i] = (float)a->items[i].data.num;
    }

    if (strcmp(filled, "fill") == 0)
        graphics_geometry_polygon(true, vertices, len * 0.5);
    else if (strcmp(filled, "line") == 0)
        graphics_geometry_polygon(false, vertices, len * 0.5);
    else {
        free(vertices);
        return fh_set_error(prog, "Expected 'fill' or 'line' for the first argument");
    }
    free(vertices);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_geometry_setLineWidth(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {

    double w = fh_get_number(&args[0]);
    graphics_geometry_setLineWidth(w);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_geometry_getLineWidth(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_geometry_getLineWidth());
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_geometry_circle),
    DEF_FN(love_geometry_rectangle),
    DEF_FN(love_geometry_points),
    DEF_FN(love_geometry_line),
    DEF_FN(love_geometry_polygon),
    DEF_FN(love_geometry_setLineWidth),
    DEF_FN(love_geometry_getLineWidth),
};

void fh_graphics_geometry_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
