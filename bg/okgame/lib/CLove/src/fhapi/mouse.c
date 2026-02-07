/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "mouse.h"

#include "../include/mouse.h"

#include "../3rdparty/FH/src/value.h"
#include "../3rdparty/SDL2/include/SDL.h"

static struct {
    struct fh_program *prog;
} moduleData;

void fh_mouse_pressed(int x, int y, int button) {
    struct fh_value _x = fh_new_number(x);
    struct fh_value _y = fh_new_number(y);
    struct fh_value _button = fh_new_string(moduleData.prog, mouse_button_to_str(button));

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 3);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = _x;
    arr->items[1] = _y;
    arr->items[2] = _button;

    if (fh_call_function(moduleData.prog, "love_mousepressed", &args, 1, NULL) < 0) {
        fh_set_error(moduleData.prog, fh_get_error(moduleData.prog));
    }
}

void fh_mouse_released(int x, int y, int button) {
    struct fh_value _x = fh_new_number(x);
    struct fh_value _y = fh_new_number(y);
    struct fh_value _button = fh_new_string(moduleData.prog, mouse_button_to_str(button));

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 3);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = _x;
    arr->items[1] = _y;
    arr->items[2] = _button;

    if (fh_call_function(moduleData.prog, "love_mousereleased", &args, 1, NULL) < 0) {
        fh_set_error(moduleData.prog, fh_get_error(moduleData.prog));
    }
}

void fh_mouse_wheelmoved(int y) {
    struct fh_value _y = fh_new_number(y);

    if (fh_call_function(moduleData.prog, "love_wheelmoved", &_y, 1, NULL) < 0) {
        fh_set_error(moduleData.prog, fh_get_error(moduleData.prog));
    }
}


static int fn_love_mouse_isDown(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(n_args);
    if (!fh_is_string(&args[0])) {
        return fh_set_error(prog, "Expected string type for arg 1, got %s\n", fh_type_to_str(prog, args[0].type));
    }

    const char *name = fh_get_string(&args[0]);
    int res = mouse_isDown(name);
    if(res < 0) {
        return fh_set_error(prog, "bad button name '%s'", name);
    }
    *ret = fh_new_bool(res);
    return 0;
}

static int fn_love_mouse_getPosition(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
   UNUSED(args);
   UNUSED(n_args);
    int x, y;
    mouse_getPosition(&x, &y);

    struct fh_value _x = fh_new_number(x);
    struct fh_value _y = fh_new_number(y);

    struct fh_value pos = fh_new_array(prog);
    fh_grow_array(prog, &pos, 2);

    struct fh_array *arr = (struct fh_array *) pos.data.obj;
    arr->items[0] = _x;
    arr->items[1] = _y;

    *ret = pos;
    return 0;
}

static int fn_love_mouse_getX(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
    UNUSED(prog);
    UNUSED(args);
    UNUSED(n_args);
    *ret = fh_new_number(mouse_getX());
    return 0;
}


static int fn_love_mouse_getY(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(args);
    UNUSED(n_args);
    *ret = fh_new_number(mouse_getY());
    return 0;
}

static int fn_love_mouse_setPosition(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
    UNUSED(ret);
    if (n_args != 2) {
        return fh_set_error(prog, "Expected 2 arguments, got: %d\n", n_args);
    }

    if (!fh_is_number(&args[0]) || !fh_is_number(&args[1])) {
        return fh_set_error(prog, "Expected two numbers, got: %s and %s\n",
                            fh_type_to_str(prog, args[0].type), fh_type_to_str(prog, args[1].type));
    }

    int x = (int)fh_get_number(&args[0]);
    int y = (int)fh_get_number(&args[1]);
    mouse_setPosition(x, y);
    return 0;
}

static int fn_love_mouse_isVisible(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
    UNUSED(prog);
    UNUSED(args);
    UNUSED(n_args);
    *ret = fh_new_bool(mouse_isVisible());
    return 1;
}

static int fn_love_mouse_setVisible(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
    UNUSED(ret);
    UNUSED(n_args);
    if (!fh_is_bool(&args[0])) {
        return fh_set_error(prog, "Expected type boolean, got %s\n", fh_type_to_str(prog, args[0].type));
    }

    mouse_setVisible(fh_get_bool(&args[0]));
    return 0;
}

static int fn_love_mouse_setX(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args)  {
    UNUSED(ret);
    UNUSED(n_args);
    if (!fh_is_number(&args[0])) {
        return fh_set_error(prog, "Expected type number, got %s\n", fh_type_to_str(prog, args[0].type));
    }
    mouse_setX((int)fh_get_number(&args[0]));
    return 0;
}

static int fn_love_mouse_setY(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(ret);
    UNUSED(n_args);
    if (!fh_is_number(&args[0])) {
        return fh_set_error(prog, "Expected type number, got %s\n", fh_type_to_str(prog, args[0].type));
    }
    mouse_setY((int)fh_get_number(&args[0]));
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_mouse_isDown),
    DEF_FN(love_mouse_setPosition),
    DEF_FN(love_mouse_getPosition),
    DEF_FN(love_mouse_getX),
    DEF_FN(love_mouse_getY),
    DEF_FN(love_mouse_isVisible),
    DEF_FN(love_mouse_setVisible),
    DEF_FN(love_mouse_setX),
    DEF_FN(love_mouse_setY),
};

void fh_mouse_register(struct fh_program* prog) {
    moduleData.prog = prog;
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
