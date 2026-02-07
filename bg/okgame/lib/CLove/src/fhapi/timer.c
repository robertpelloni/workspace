/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "timer.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/timer.h"

int fn_love_timer_step(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(ret);
    UNUSED(args);
    UNUSED(n_args);

    timer_step();
    return 0;
}

int fn_love_timer_getTime(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(timer_getTime());
    return 1;
}

int fn_love_timer_getFPS(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number((int)(timer_getFPS()+0.5f));
    return 1;
}

int fn_love_timer_getDelta(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(timer_getDelta());
    return 1;
}

int fn_love_timer_getAverageDelta(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(timer_getAverageDelta());
    return 1;
}

int fn_love_timer_sleep(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[0])) {
        return fh_set_error(prog,"Expected number, got: %s\n", fh_type_to_str(prog, args[0].type));
    }
    timer_sleep((short)fh_get_number(&args[0]));
    *ret = fh_new_null();
    return 1;
}


#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_timer_step),
    DEF_FN(love_timer_getTime),
    DEF_FN(love_timer_getFPS),
    DEF_FN(love_timer_getDelta),
    DEF_FN(love_timer_getAverageDelta),
    DEF_FN(love_timer_sleep),
};

void fh_timer_register(struct fh_program* prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
