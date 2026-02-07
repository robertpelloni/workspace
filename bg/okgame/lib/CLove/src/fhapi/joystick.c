/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "joystick.h"

#include "../include/joystick.h"

#include "../3rdparty/FH/src/value.h"

/*
 * TODO:
 * Finish this once you know the current code works
 */

static struct {
    struct fh_program *prog;
} moduleData;

void fh_joystick_pressed(int id, int button) {
    struct fh_value _id = fh_new_number(id);
    struct fh_value button_str = fh_new_string(moduleData.prog,
            joystick_convert_button_to_str(button));

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 2);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = _id;
    arr->items[1] = button_str;


    if (fh_call_function(moduleData.prog, "love_joystickpressed", &args, 1, NULL) < 0) {
        fh_set_error(moduleData.prog, "Error: %s\n", fh_get_error(moduleData.prog));
    }
}

void fh_joystick_released(int id, int button) {
    struct fh_value _id = fh_new_number(id);
    struct fh_value button_str = fh_new_string(moduleData.prog,
            joystick_convert_button_to_str(button));

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 2);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = _id;
    arr->items[1] = button_str;


    if (fh_call_function(moduleData.prog, "love_joystickreleased", &args, 1, NULL) < 0) {
        fh_set_error(moduleData.prog, "Error: %s\n", fh_get_error(moduleData.prog));
    }
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {

};

void fh_joystick_register(struct fh_program *prog) {
    moduleData.prog = prog;
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
