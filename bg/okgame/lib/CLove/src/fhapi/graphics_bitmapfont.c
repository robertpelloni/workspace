/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "graphics_bitmapfont.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/bitmap_font.h"

static void gcFont(graphics_BitmapFont *font) {
    graphics_BitmapFont_free(font);
    free(font);
}

static int fn_love_graphics_newBitmapFont(struct fh_program *prog,
                                          struct fh_value *ret, struct fh_value *args, int n_args)
{
    if (n_args < 2)
        return fh_set_error(prog, "Illegal number of arguments, expected 5");

    if (!fh_is_string(&args[0]) || !fh_get_string(&args[1]))
        return fh_set_error(prog, "Illegal argument type");

    const char *filename = fh_get_string(&args[0]);
    const char *glyphs = fh_get_string(&args[1]);
    int gw = (int)fh_optnumber(args, n_args, 2, 0.0);
    int gh = (int)fh_optnumber(args, n_args, 3, 0.0);
    int max_size = (int)fh_optnumber(args, n_args, 4, 128.0);

    fh_c_obj_gc_callback *freeCallback = gcFont;

    graphics_BitmapFont *font = malloc(sizeof (graphics_BitmapFont));

    graphics_BitmapFont_new(font, filename, max_size, glyphs, gw, gh);

    *ret = fh_new_c_obj(prog, font, freeCallback, FH_BITMAP_FONT_TYPE);

    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newBitmapFont),
};

void fh_graphics_bitmap_font_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
