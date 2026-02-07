/*
#   clove
#
#   Copyright (C) 2016-2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "keyboard.h"

#include "../include/keyboard.h"
#include "tools.h"

#include "../3rdparty/FH/src/value.h"

static struct {
    struct fh_program *prog;
    bool keyRepeat;
} moduleData;

int fh_keyboard_keypressed(SDL_Keycode key, bool repeat) {
    if(repeat && !moduleData.keyRepeat) {
        return -1;
    }
    struct fh_value keyName = fh_new_string(moduleData.prog, keyboard_getKeyName(key));
    struct fh_value keyAsNumber = fh_new_number(key);
    struct fh_value isrepeat = fh_new_bool(repeat);

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 3);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = keyName;
    arr->items[1] = keyAsNumber;
    arr->items[2] = isrepeat;

    if (fh_call_function(moduleData.prog, "love_keypressed", &args, 1, NULL) < 0) {
        return fh_set_error(moduleData.prog, "ERROR: %s\n", fh_get_error(moduleData.prog));
    }
    return 0;
}

int fh_keyboard_keyreleased(SDL_Keycode key) {
    struct fh_value keyName = fh_new_string(moduleData.prog, keyboard_getKeyName(key));
    struct fh_value keyAsNumber = fh_new_number(key);

    struct fh_value args = fh_new_array(moduleData.prog);
    fh_grow_array(moduleData.prog, &args, 2);

    struct fh_array *arr = (struct fh_array *) args.data.obj;
    arr->items[0] = keyName;
    arr->items[1] = keyAsNumber;

    if (fh_call_function(moduleData.prog, "love_keyreleased", &args, 1, NULL) < 0) {
        return fh_set_error(moduleData.prog, "ERROR: %s\n", fh_get_error(moduleData.prog));
    }
    return 0;
}

int fh_keyboard_textInput(char const* text) {
    struct fh_value textObj = fh_new_string(moduleData.prog, text);
    if (fh_call_function(moduleData.prog, "love_textinput", &textObj, 1, NULL) < 0) {
        return fh_set_error(moduleData.prog, "ERROR: %s\n", fh_get_error(moduleData.prog));
    }
    return 0;
}

static int fn_love_keyboard_isDown(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    bool any = false;
    for(int i = 0; i < n_args; ++i) {
        if (!fh_is_string(&args[i]))
            return fh_set_error(prog, "Expected string value, got: %s\n", fh_type_to_str(prog, args[i].type));

        any = any || keyboard_ispressed(
                    keyboard_getKeycode(GET_VAL_STRING_DATA(&args[i])));
        if(any)
            break;
    }

    *ret = fh_new_bool(any);
    return 0;
}

int fn_love_keyboard_setKeyRepeat(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1) {
        return fh_set_error(prog, "Expected one argument of type boolean, got %s", fh_type_to_str(prog, args[0].type));
    }
    moduleData.keyRepeat = fh_get_bool(&args[0]);
    return 0;
}

int fn_love_keyboard_hasKeyRepeat(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    *ret = fh_new_bool(moduleData.keyRepeat);
    return 0;
}

int fn_love_keyboard_setTextInput(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1) {
        return fh_set_error(prog, "Expected one argument of type boolean, got %s", fh_type_to_str(prog, args[0].type));
    }
    if(fh_get_bool(&args[0])) {
        keyboard_startText();
    } else {
        keyboard_stopText();
    }
    *ret = fh_new_null();
    return 0;
}

int fn_love_keyboard_hasTextInput(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(args);
    *ret = fh_new_bool(keyboard_isTextEnabled());
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_keyboard_isDown),
    DEF_FN(love_keyboard_setKeyRepeat),
    DEF_FN(love_keyboard_hasKeyRepeat),
    DEF_FN(love_keyboard_setTextInput),
    DEF_FN(love_keyboard_hasTextInput),
};

void fh_keyboard_register(struct fh_program *prog) {
    moduleData.prog = prog;
    moduleData.keyRepeat = false;
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
