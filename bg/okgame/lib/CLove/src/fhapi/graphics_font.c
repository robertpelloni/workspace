/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "graphics_font.h"
#include "graphics_bitmapfont.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/font.h"
#include "../include/matrixstack.h"
#include "../include/graphics.h"
#include "../include/bitmap_font.h"

static struct {
    graphics_Font defaultFont;
    graphics_Font *currentFont;
    int currentFontSize;
    graphics_BitmapFont *currentBitmapFont;
    /**
     * When this is set to true then we're rendering a bitmap image font
     */
    bool isBitmapFont;
} moduleData;

static fh_c_obj_gc_callback gcFont(graphics_Font *font) {
    graphics_Font_free(font);
    free(font);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_graphics_newFont(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    const char *filename = NULL;
    moduleData.currentFontSize = 12;

    if (!fh_is_null(&args[0])) {
        enum fh_value_type type = args[0].type;
        if (type == FH_VAL_STRING) {
            filename = fh_get_string(&args[0]);
            if (fh_is_number(&args[1])) {
                moduleData.currentFontSize = (int)fh_get_number(&args[1]);
            }
        } else if (type == FH_VAL_FLOAT){
            moduleData.currentFontSize = (int)fh_get_number(&args[0]);
        } else {
            return fh_set_error(prog, "Illegal parameter, expected null, string or number for the first argument");
        }
    }

    graphics_Font *font = malloc(sizeof(graphics_Font));
    int err = graphics_Font_new(font, filename, moduleData.currentFontSize);
    if (err != 0)
        return fh_set_error(prog, "Error loading font");

    fh_c_obj_gc_callback *callback = gcFont;
    *ret = fh_new_c_obj(prog, font, callback, FH_FONT_TYPE);
    return 0;
}

static void graphics_loadDefaultFont() {
    moduleData.currentFontSize = 12;
    graphics_Font_new(&moduleData.defaultFont, NULL, 12);
    moduleData.currentFont = &moduleData.defaultFont;
}

static int fn_love_graphics_setFont(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {

    if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        moduleData.isBitmapFont = false;
        moduleData.currentFont = fh_get_c_obj_value(&args[0]);
    } else if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        moduleData.isBitmapFont = true;
        moduleData.currentBitmapFont = fh_get_c_obj_value(&args[0]);
    } else if (fh_is_number(&args[0])) {
        moduleData.isBitmapFont = false;
        graphics_Font_new(&moduleData.defaultFont, NULL, (int)fh_get_number(&args[0]));
        moduleData.currentFont = &moduleData.defaultFont;
    } else {
        return fh_set_error(prog, "Expected font, number or image font");
    }

    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getFont(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    if (moduleData.isBitmapFont) {
        *ret = fh_new_c_obj(prog, moduleData.currentBitmapFont, NULL, FH_BITMAP_FONT_TYPE);
    } else {
		if (!moduleData.currentFont) {
			*ret = fh_new_null();
			return 0;
		}
        *ret = fh_new_c_obj(prog, moduleData.currentFont, NULL, FH_FONT_TYPE);
    }
    return 0;
}

static int fn_love_graphics_print(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_string(&args[0]))
        return fh_set_error(prog, "Expected string");

    if (!moduleData.currentFont && !moduleData.isBitmapFont) {
        graphics_loadDefaultFont();
    }

    const char *text = fh_get_string(&args[0]);

    int x = fh_optnumber(args, n_args, 1, 0);
    int y = fh_optnumber(args, n_args, 2, 0);
    int r = fh_optnumber(args, n_args, 3, 0);
    int sx = fh_optnumber(args, n_args, 4, 1.0);
    int sy = fh_optnumber(args, n_args, 5, 1.0);
    int ox = fh_optnumber(args, n_args, 6, 0);
    int oy = fh_optnumber(args, n_args, 7, 0);
    int kx = fh_optnumber(args, n_args, 8, 0);
    int ky = fh_optnumber(args, n_args, 9, 0);

    if (moduleData.isBitmapFont) {
        graphics_BitmapFont_render(moduleData.currentBitmapFont, text, x, y, r, sx, sy, ox, oy, kx, ky);
    } else {
        graphics_Font_render(moduleData.currentFont, text, x, y, r, sx, sy, ox, oy, kx, ky);
    }
    *ret = fh_new_null();
    return 0;
}

static int fn_love_font_getHeight(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        graphics_Font *font = fh_get_c_obj_value(&args[0]);

        *ret = fh_new_number((int)graphics_Font_getHeight(font));
    } else if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        graphics_BitmapFont *font = fh_get_c_obj_value(&args[0]);

        *ret = fh_new_number((int)font->image->height);
    } else {
        *ret = fh_new_number((int) graphics_Font_getHeight(&moduleData.defaultFont));
    }
    return 0;
}

static int fn_love_font_getWidth(struct fh_program *prog,
                                 struct fh_value *ret, struct fh_value *args, int n_args) {
    int string_index = 0;
    if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        if (!fh_is_string(&args[1])) {
            return fh_set_error(prog, "Expected string");
        }
        string_index = 1;
    } else {
        if (!fh_is_string(&args[0])) {
            return fh_set_error(prog, "Expected string");
        }
    }

    char const *line = fh_get_string(&args[string_index]);

    graphics_Font *font;
    graphics_BitmapFont *bitmap;

    if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        font = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number((int)graphics_Font_getWidth(font, line));
    } else if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        bitmap = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number((int)graphics_BitmapFont_getWidth(bitmap, line));
    } else {
        *ret = fh_new_number((int) graphics_Font_getWidth(&moduleData.defaultFont, line));
    }

    return 0;
}

static int fn_love_font_getDescent(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        return fh_set_error(prog, "Expected font");
    }
    graphics_Font *font = fh_get_c_obj_value(&args[0]);

    *ret = fh_new_number((int)graphics_Font_getDescent(font));
    return 0;
}

static int fn_love_font_getAscent(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        return fh_set_error(prog, "Expected font");
    }
    graphics_Font *font = fh_get_c_obj_value(&args[0]);

    *ret = fh_new_number((int)graphics_Font_getAscent(font));
    return 0;
}

static int fn_love_font_getBaseline(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        return fh_set_error(prog, "Expected font");
    }
    graphics_Font *font = fh_get_c_obj_value(&args[0]);

    *ret = fh_new_number((int)graphics_Font_getBaseline(font));
    return 0;
}


static int fn_love_font_getWrap(struct fh_program *prog,
                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_string(&args[1]) || !fh_is_number(&args[2])) {
        return fh_set_error(prog, "Expected string and wrap limit");
    }
    graphics_Font *font;
    graphics_BitmapFont *bitmap;
    bool isBitmap = false;

    if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE))
        font = fh_get_c_obj_value(&args[0]);
    else if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        isBitmap = true;
        bitmap = fh_get_c_obj_value(&args[0]);
    } else {
        return fh_set_error(prog, "Expected font or bitmap font");
    }

    const char *line = fh_get_string(&args[1]);
    int wraplimit = (int)fh_get_number(&args[2]);

    char *wrappedtext = malloc(strlen(line));
    int wrappedlines;

    if (isBitmap) {
        wrappedlines = graphics_BitmapFont_getWrap(bitmap, line, wraplimit, &wrappedtext);
    } else {
        wrappedlines = graphics_Font_getWrap(font, line, wraplimit, &wrappedtext);
    }

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_string(prog, wrappedtext);
    ret_arr->items[1] = fh_new_number((int)wrappedlines);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    free(wrappedtext);
    return 0;
}

static int fn_love_font_setFilter(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args < 3) {
        return fh_set_error(prog, "Expected 3 arguments!");
    }

    graphics_Font *font = NULL;
    graphics_BitmapFont *bitmapFont = NULL;
    bool isBitmapFont = false;

    if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        isBitmapFont = true;
        bitmapFont = fh_get_c_obj_value(&args[0]);
    } else if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        font = fh_get_c_obj_value(&args[0]);
    } else {
        return fh_set_error(prog, "Expected bitmap font or ttf font");
    }

    if (!fh_is_string(&args[1]) || !fh_is_string(&args[2])) {
        return fh_set_error(prog, "Expected minMode and magMode as strings");
    }

    const char *min = fh_get_string(&args[1]);
    const char *mag = fh_get_string(&args[2]);

    graphics_Filter newFilter;

    newFilter.maxAnisotropy = (float)fh_optnumber(args, n_args, 3, 1.0);

    if (strcmp(min, "none") == 0) {
        newFilter.minMode = graphics_FilterMode_none;
    } else if (strcmp(min, "linear") == 0) {
        newFilter.minMode = graphics_FilterMode_linear;
    } else if (strcmp(min, "nearest") == 0) {
        newFilter.minMode = graphics_FilterMode_nearest;
    }

    if (strcmp(mag, "none") == 0) {
        newFilter.magMode = graphics_FilterMode_none;
    } else if (strcmp(mag, "linear") == 0) {
        newFilter.magMode = graphics_FilterMode_linear;
    } else if (strcmp(mag, "nearest") == 0) {
        newFilter.magMode = graphics_FilterMode_nearest;
    }

    if (isBitmapFont) {
        graphics_BitmapFont_setFilter(bitmapFont, &newFilter);
    } else {
        graphics_Font_setFilter(font, &newFilter);
    }

    *ret = fh_new_null();
    return 0;
}

static int fn_love_font_getFilter(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    graphics_Font *font = NULL;
    graphics_BitmapFont *bitmapFont = NULL;
    bool isBitmapFont = false;

    graphics_Filter filter;

    if (fh_is_c_obj_of_type(&args[0], FH_BITMAP_FONT_TYPE)) {
        isBitmapFont = true;
        bitmapFont = fh_get_c_obj_value(&args[0]);
        graphics_BitmapFont_getFilter(bitmapFont, &filter);
    } else if (fh_is_c_obj_of_type(&args[0], FH_FONT_TYPE)) {
        font = fh_get_c_obj_value(&args[0]);
        graphics_Font_getFilter(font, &filter);
    } else {
        return fh_set_error(prog, "Expected bitmap font or ttf font");
    }

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, arr, 3))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    if (filter.minMode == graphics_FilterMode_none)
        arr->items[0] = fh_new_string(prog, "none");
    else if (filter.minMode == graphics_FilterMode_linear)
        arr->items[0] = fh_new_string(prog, "linear");
    else if (filter.minMode == graphics_FilterMode_nearest)
        arr->items[0] = fh_new_string(prog, "nearest");

    if (filter.magMode == graphics_FilterMode_none)
        arr->items[1] = fh_new_string(prog, "none");
    else if (filter.magMode == graphics_FilterMode_linear)
        arr->items[1] = fh_new_string(prog, "linear");
    else if (filter.magMode == graphics_FilterMode_nearest)
        arr->items[1] = fh_new_string(prog, "nearest");

    arr->items[2] = fh_new_number((double)filter.maxAnisotropy);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = arr;
    *ret = new_val;

    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newFont),
    DEF_FN(love_graphics_setFont),
    DEF_FN(love_graphics_getFont),
    DEF_FN(love_font_getHeight),
    DEF_FN(love_font_getWidth),
    DEF_FN(love_font_getBaseline),
    DEF_FN(love_font_getAscent),
    DEF_FN(love_font_getDescent),
    DEF_FN(love_font_getWrap),
    DEF_FN(love_font_setFilter),
    DEF_FN(love_font_getFilter),
    DEF_FN(love_graphics_print),
};

void fh_graphics_font_register(struct fh_program *prog) {
    moduleData.currentFont = NULL;
    moduleData.currentBitmapFont = NULL;
    moduleData.isBitmapFont = false;

    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
