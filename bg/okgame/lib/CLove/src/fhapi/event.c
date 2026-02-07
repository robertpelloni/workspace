/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "event.h"

#include "../include/utils.h"

static int fn_love_event_quit(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    clove_running = false;
    *ret = fh_new_null();
    return 0;
}

static int fn_love_event_reload(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    clove_reload = true;
    *ret = fh_new_null();
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_event_quit),
    DEF_FN(love_event_reload),
};

void fh_event_register(struct fh_program *prog) {
    clove_running = true;
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
