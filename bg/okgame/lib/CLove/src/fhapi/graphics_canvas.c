/*
#   clove
#
#   Copyright (C) 2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "../3rdparty/FH/src/value.h"

#include "../include/canvas.h"

#include "graphics_canvas.h"

static fh_c_obj_gc_callback gcCanvas(graphics_Canvas *c) {
    graphics_Canvas_free(c);
    free(c);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_graphics_newCanvas(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {

    if (n_args != 2) {
        return fh_set_error(prog, "Expected 2 arguments, width and height");
    }

    for (int i = 0; i < 2; i++) {
        if (!fh_is_number(&args[i])) {
            return fh_set_error(prog, "Expected number at argument %d", i);
        }
    }

    int width = fh_get_number(&args[0]);
    int height = fh_get_number(&args[1]);

    graphics_Canvas *c = malloc(sizeof(graphics_Canvas));

    graphics_Canvas_new(c, width, height);

    fh_c_obj_gc_callback *callback = gcCanvas;

    *ret = fh_new_c_obj(prog, c, callback, FH_GRAPHICS_CANVAS);
    return 0;
}

static int fn_love_graphics_setCanvas(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {

    if (fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_CANVAS)) {
       graphics_Canvas *c = fh_get_c_obj_value(&args[0]);
       graphics_setCanvas(c);
    } else {
        graphics_setCanvas(NULL);
    }

    *ret = fh_new_null();
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newCanvas),
    DEF_FN(love_graphics_setCanvas)
};

void fh_graphics_canvas_register(struct fh_program *prog) {
     fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
