/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "love.h"

#include "../include/love.h"

#include "../3rdparty/FH/src/value.h"

static int fn_love_getVersion(struct fh_program *prog,
        struct fh_value *ret, struct fh_value *args, int n_args) {

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    love_Version const * version = love_getVersion();
    ret_arr->items[0] = fh_new_number(version->major);
    ret_arr->items[1] = fh_new_number(version->minor);
    ret_arr->items[2] = fh_new_number(version->revision);
    ret_arr->items[3] = fh_new_string(prog, version->codename);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_getVersion)
};

void fh_love_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
