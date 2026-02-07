/*
#   clove
#
#   Copyright (C) 2019-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "graphics_window.h"
#include "image.h"

#include "../include/graphics.h"

#include "../3rdparty/FH/src/value.h"

int fn_love_window_getWidth(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_getWidth());
    return 0;
}

int fn_love_window_getHeight(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_getHeight());
    return 0;
}

int fn_love_window_getDimensions(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    int w = graphics_getWidth();
    int h = graphics_getHeight();

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number(w);
    ret_arr->items[1] = fh_new_number(h);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

int fn_love_window_getDesktopDimension(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    int *r = graphics_getDesktopDimension();
    int w = r[0];
    int h = r[1];

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number(w);
    ret_arr->items[1] = fh_new_number(h);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

int fn_love_window_getDisplayCount(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_getDisplayCount());
    return 0;
}

int fn_love_window_setIcon(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {

    if (!fh_is_c_obj_of_type(&args[0], FH_IMAGE_TYPE))
        return fh_set_error(prog, "Illegal argument, expected image");

    fh_image_t *imgd = fh_get_c_obj_value(&args[0]);
    graphics_setIcon(imgd->data);
    return 0;
}

int fn_love_window_getIcon(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    image_ImageData *imgd = graphics_getIcon();
    *ret = fh_new_c_obj(prog, imgd, NULL, FH_IMAGE_TYPE);
    return 0;
}

int fn_love_window_setTitle(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1 || !fh_is_string(&args[0]))
        return fh_set_error(prog, "Expected string");

    const char *title = fh_get_string(&args[0]);
    graphics_setTitle(title);
    *ret = fh_new_null();
    return  0;
}

int fn_love_window_setVsync(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1 || !fh_is_bool(&args[0]))
        return fh_set_error(prog, "Expected boolean");
    graphics_setVsync(&args[0]);
    *ret = fh_new_null();
    return 0;
}

int fn_love_window_getDisplayName(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    int index = (int)fh_optnumber(&args[0], n_args, 0, 0);
    const char *name = graphics_getDisplayName(index);
    *ret = fh_new_string(prog, name);
    return 0;
}

int fn_love_window_setFullscreen(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 2 || !fh_is_bool(&args[0]) || !fh_is_string(&args[1]))
        return fh_set_error(prog, "Expected fullscreen value and string mode");

    bool fullscreen = fh_get_bool(&args[0]);
    const char *mode = fh_get_string(&args[1]);

    graphics_setFullscreen(fullscreen, mode);
    *ret = fh_new_null();
    return 0;
}

int fn_love_window_isCreated(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_bool(graphics_isCreated());
    return 0;
}

int fn_love_window_getTitle(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_string(prog, graphics_getTitle());
    return 0;
}

int fn_love_window_setPosition(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 2 || !fh_is_number(&args[0]) || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected parameters, x and y to be numbers");

    int x = (int)fh_get_number(&args[0]);
    int y = (int)fh_get_number(&args[1]);

    graphics_setPosition(x, y);
    *ret = fh_new_null();
    return 0;
}

int fn_love_window_hasFocus(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_bool(graphics_hasFocus());
    return 0;
}


int fn_love_window_hasMouseFocus(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_bool(graphics_hasMouseFocus());
    return 0;
}

int fn_love_window_setMode(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {

    for (int i = 0; i < 2; i++) {
        if (!fh_is_number(&args[i]))
            return fh_set_error(prog, "Invalid argument, expected number");
    }

    double w = fh_get_number(&args[0]);
    double h = fh_get_number(&args[1]);
    bool fullscreen = fh_optboolean(args, n_args, 2, false);
    bool vsync = fh_optboolean(args, n_args, 3, true);
    double m_s_x = fh_optnumber(args, n_args, 4, w / 2);
    double m_s_y = fh_optnumber(args, n_args, 5, h / 2);
    double ma_s_x = fh_optnumber(args, n_args, 6, w);
    double ma_s_y = fh_optnumber(args, n_args, 7, h);
    bool border = fh_optboolean(args, n_args, 8, true);
    double x = fh_optnumber(args, n_args, 9, -1);
    double y = fh_optnumber(args, n_args, 10, -1);

    graphics_setMode(w, h, fullscreen, vsync, m_s_x, m_s_y, ma_s_x, ma_s_y, border, x, y);
    *ret = fh_new_null();
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_window_getWidth),
    DEF_FN(love_window_getHeight),
    DEF_FN(love_window_getDimensions),
    DEF_FN(love_window_getDesktopDimension),
    DEF_FN(love_window_getDisplayCount),
    DEF_FN(love_window_setIcon),
    DEF_FN(love_window_getIcon),
    DEF_FN(love_window_setTitle),
    DEF_FN(love_window_getDisplayName),
    DEF_FN(love_window_setFullscreen),
    DEF_FN(love_window_isCreated),
    DEF_FN(love_window_getTitle),
    DEF_FN(love_window_setPosition),
    DEF_FN(love_window_hasFocus),
    DEF_FN(love_window_hasMouseFocus),
    DEF_FN(love_window_setMode),
    DEF_FN(love_window_setVsync),
};


void fh_graphics_window_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
