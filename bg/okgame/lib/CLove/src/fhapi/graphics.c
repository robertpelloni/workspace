/*
#   clove
#
#   Copyright (C) 2019-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "graphics.h"

#include "../3rdparty/FH/src/value.h"
#include "../3rdparty/CMath/cmath.h"

#include "image.h"
#include "graphics_batch.h"
#include "graphics_mesh.h"
#include "graphics_particlesystem.h"
#include "graphics_quad.h"
#include "graphics_canvas.h"

#include "../include/graphics.h"
#include "../include/matrixstack.h"
#include "../include/shader.h"
#include "../include/batch.h"
#include "../include/mesh.h"
#include "../include/particlesystem.h"
#include "../include/canvas.h"

static int fn_love_graphics_setBackgroundColor(struct fh_program *prog,
                                               struct fh_value *ret, struct fh_value *args, int n_args) {

    if (!fh_is_number(&args[0]))
        return fh_set_error(prog, "Expected number");

    double red = fh_get_number(&args[0]);

    double green = fh_optnumber(args, n_args, 1, red);
    double blue = fh_optnumber(args, n_args, 2, green);
    double alpha = fh_optnumber(args, n_args, 3, 255.0);

    float scale = 1.0f / 255.0f;

    graphics_setBackgroundColor((float)red * scale, (float)green * scale, (float) blue * scale, (float) alpha * scale);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getBackgroundColor(struct fh_program *prog,
                                               struct fh_value *ret, struct fh_value *args, int n_args) {
    float *colors = graphics_getBackgroundColor();

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    for (int i = 0; i < 4; i++)
        ret_arr->items[i] = fh_new_number((double)colors[i] * 255.0);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

static int fn_love_graphics_setColor(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[0]))
        return fh_set_error(prog, "Expected number");

    double red = fh_get_number(&args[0]);
    double green = fh_optnumber(args, n_args, 1, red);
    double blue = fh_optnumber(args, n_args, 2, green);
    double alpha = fh_optnumber(args, n_args, 3, 255.0);

    float scale = 1.0f / 255.0f;

    graphics_setColor((float)red * scale, (float)green * scale, (float)blue * scale, (float)alpha * scale);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getColor(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    float *colors = graphics_getColor();

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    fh_grow_array_object(prog, ret_arr, 4);

    struct fh_value new_val = fh_new_array(prog);

    for (int i = 0; i < 4; i++)
        ret_arr->items[i] = fh_new_number((double)colors[i] * 255.0);

    new_val.data.obj = ret_arr;
    fh_restore_pin_state(prog, pin_state);
    *ret = new_val;
    return 0;
}

static int fn_love_graphics_clear(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    graphics_clear();
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_push(struct fh_program *prog,
                                 struct fh_value *ret, struct fh_value *args, int n_args) {
    if(matrixstack_push()) {
        return fh_set_error(prog, "Matrix stack overflow\n");
    }
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_pop(struct fh_program *prog,
                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if(matrixstack_pop()) {
        return fh_set_error(prog, "Matrix stack underrun\n");
    }
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_translate(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[0]) || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected at least 2 numbers as arguments\n");

    float x = (float)fh_get_number(&args[0]);
    float y = (float)fh_get_number(&args[1]);
    float z = (float)fh_optnumber(args, n_args, 2, 1.0);

    matrixstack_translate(x, y, z);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_scale(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[0]) || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected at least 2 numbers as arguments\n");

    float x = (float)fh_get_number(&args[0]);
    float y = (float)fh_get_number(&args[1]);
    float z = (float)fh_optnumber(args, n_args, 2, 1.0);

    matrixstack_scale(x, y, z);
    *ret = fh_new_null();
    return 0;
}


static int fn_love_graphics_rotate(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[0]) )
        return fh_set_error(prog, "Expected number as argument\n");

    float a = (float)fh_get_number(&args[0]);

    matrixstack_rotate(a);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_origin(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    matrixstack_origin();
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_shear(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (! (fh_is_number(&args[0]) && fh_is_number(&args[1])) )
        return fh_set_error(prog, "Expected exactly 2 numbers as arguments\n");

    float kx = (float)fh_get_number(&args[0]);
    float ky = (float)fh_get_number(&args[1]);

    graphics_shear(kx, ky);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_setColorMask(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_null(&args[0])) {
        graphics_setColorMask(true, true, true, true);
        return 0;
    } else {
        for (int i = 0; i < 4; ++i) {
            if (!fh_is_bool(&args[i])) {
                return fh_set_error(prog, "illegal parameters");
            }
        }
    }

    bool r = fh_get_bool(&args[0]);
    bool g = fh_get_bool(&args[1]);
    bool b = fh_get_bool(&args[2]);
    bool a = fh_get_bool(&args[3]);

    graphics_setColorMask(r, g, b, a);
    *ret = fh_new_null();

    return 0;
}

static int fn_love_graphics_getColorMask(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    bool r, g, b, a;
    graphics_getColorMask(&r, &g, &b, &a);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_bool(r);
    ret_arr->items[1] = fh_new_bool(g);
    ret_arr->items[2] = fh_new_bool(b);
    ret_arr->items[3] = fh_new_bool(a);

    new_val.data.obj = ret_arr;
    *ret = new_val;

    fh_restore_pin_state(prog, pin_state);
    return 0;
}

static int fn_love_graphics_getWidth(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_getWidth());
    return 0;
}

static int fn_love_graphics_getHeight(struct fh_program *prog,
                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    *ret = fh_new_number(graphics_getHeight());
    return 0;
}

static int fn_love_graphics_reset(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    graphics_reset();
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_setBlendMode(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 1) {
        return fh_set_error(prog, "Expected one argument of type string");
    }

    graphics_BlendMode mode;
    const char *blendType = fh_get_string(&args[0]);
    if (strcmp(blendType, "additive") == 0) {
        mode = graphics_BlendMode_additive;
    } else if (strcmp(blendType, "alpha") == 0) {
        mode = graphics_BlendMode_alpha;
    } else if (strcmp(blendType, "subtract") == 0) {
        mode = graphics_BlendMode_subtractive;
    } else if (strcmp(blendType, "multiplicative") == 0) {
        mode = graphics_BlendMode_multiplicative;
    } else if (strcmp(blendType, "premultiplied") == 0) {
        mode = graphics_BlendMode_premultiplied;
    } else if (strcmp(blendType, "replace") == 0) {
        mode = graphics_BlendMode_replace;
    } else if (strcmp(blendType, "screen") == 0) {
        mode = graphics_BlendMode_screen;
    } else {
        return fh_set_error(prog, "Invalid argument");
    }
    graphics_setBlendMode(mode);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getBlendMode(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    graphics_BlendMode mode = graphics_getBlendMode();
    switch (mode) {
    case graphics_BlendMode_additive:
        *ret = fh_new_string(prog, "additive");
        break;
    case graphics_BlendMode_alpha:
        *ret = fh_new_string(prog, "alpha");
        break;
    case graphics_BlendMode_subtractive:
        *ret = fh_new_string(prog, "subtract");
        break;
    case graphics_BlendMode_multiplicative:
        *ret = fh_new_string(prog, "multiplicative");
        break;
    case graphics_BlendMode_premultiplied:
        *ret = fh_new_string(prog, "premultiplied");
        break;
    case graphics_BlendMode_replace:
        *ret = fh_new_string(prog, "replace");
        break;
    case graphics_BlendMode_screen:
        *ret = fh_new_string(prog, "screen");
        break;
    }
    return 0;
}

static int fn_love_graphics_setScissor(struct fh_program *prog,
                                       struct fh_value *ret, struct fh_value *args, int n_args) {

    if(n_args == 0) {
        graphics_clearScissor();
        return 0;
    } else {
        for(int i = 0; i < 4; ++i) {
            if(!fh_is_number(&args[i])) {
                return fh_set_error(prog, "illegal parameter");
            }
        }
    }

    int x = fh_get_number(&args[0]);
    int y = fh_get_number(&args[1]);
    int w = fh_get_number(&args[2]);
    int h = fh_get_number(&args[3]);

    graphics_setScissor(x, y, w, h);
    *ret = fh_new_null();

    return 0;
}

static int fn_love_graphics_getScissor(struct fh_program *prog,
                                       struct fh_value *ret, struct fh_value *args, int n_args) {

    int x, y, w, h;
    bool scissor = graphics_getScissor(&x, &y, &w, &h);

    if(!scissor) {
        return 0;
    }

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    arr->items[0] = fh_new_number(x);
    arr->items[1] = fh_new_number(y);
    arr->items[2] = fh_new_number(w);
    arr->items[3] = fh_new_number(h);

    new_val.data.obj = arr;
    *ret = new_val;
    fh_restore_pin_state(prog, pin_state);
    return 0;
}

static int fn_love_graphics_getMaxAnisotropy(struct fh_program *prog,
                                             struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(args);
    if (n_args != 0)
        return fh_set_error(prog, "Unexpected argument");
    *ret = fh_new_number((double)graphics_Texture_getMaxAnisotropy());

    return 0;
}

static const graphics_Quad defaultQuad = {
    .x = 0.0f,
    .y = 0.0f,
    .w = 1.0f,
    .h = 1.0f
};

static int fn_love_graphics_draw(struct fh_program *prog,
                                 struct fh_value *ret, struct fh_value *args, int n_args) {

    if (!fh_is_c_obj(&args[0]))
        return fh_set_error(prog, "Expected image, batch, mesh, canvas or particle as first argument, got '%s'",
                            fh_type_to_str(prog, args[0].type));

    struct fh_c_obj *o = fh_get_c_obj(&args[0]);
    int index = 1;

    const graphics_Quad *quad = &defaultQuad;
    if (fh_is_c_obj_of_type(&args[index], FH_GRAPHICS_QUAD)) {
        quad = fh_get_c_obj_value(&args[index]);
        index ++;
    }

    float x = (float)fh_optnumber(args, n_args, index, 0.0);
    float y = (float)fh_optnumber(args, n_args, index + 1, 0.0);
    float r = (float)fh_optnumber(args, n_args, index + 2, 0.0);
    float sx = (float)fh_optnumber(args, n_args, index + 3, 1.0);
    float sy = (float)fh_optnumber(args, n_args, index + 4, 1.0);
    float ox = (float)fh_optnumber(args, n_args, index + 5, 0.0);
    float oy = (float)fh_optnumber(args, n_args, index + 6, 0.0);
    float kx = (float)fh_optnumber(args, n_args, index + 7, 0.0);
    float ky = (float)fh_optnumber(args, n_args, index + 8, 0.0);

    if (o->type == FH_IMAGE_TYPE) {
        fh_image_t *image = fh_get_c_obj_value(&args[0]);
        graphics_Image_draw(image->img, quad, x, y, r, sx, sy, ox, oy, kx, ky);
    } else if (o->type == FH_GRAPHICS_BATCH) {
        graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
        graphics_Batch_draw(batch, x, y, r, sx, sy, ox, oy, kx, ky);
    } else if (o->type == FH_GRAPHICS_MESH) {
        graphics_Mesh *mesh = fh_get_c_obj_value(&args[0]);
        graphics_Mesh_draw(mesh, x, y, r, sx, sy, ox, oy, kx, ky);
    } else if (o->type == FH_GRAPHICS_PARTICLE) {
        graphics_ParticleSystem *particle = fh_get_c_obj_value(&args[0]);
        graphics_ParticleSystem_draw(particle, x, y, r, sx, sy, ox, oy, kx, ky);
    } else if (o->type == FH_GRAPHICS_CANVAS) {
        graphics_Canvas *canvas = fh_get_c_obj_value(&args[0]);
        graphics_Canvas_draw(canvas, quad, x, y, r, sx, sy, ox, oy, kx, ky);
    }  else
        return fh_set_error(prog, "Expected image, batch, mesh, canvas or particle as first argument, got '%s'",
                            fh_type_to_str(prog, args[0].type));

    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_getDPIScale(struct fh_program *prog,
                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    UNUSED(prog);
    UNUSED(args);
    UNUSED(n_args);
    *ret = fh_new_number( (double) graphics_getDPIScale());
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_setBackgroundColor),
    DEF_FN(love_graphics_getBackgroundColor),
    DEF_FN(love_graphics_setColor),
    DEF_FN(love_graphics_getColor),
    DEF_FN(love_graphics_push),
    DEF_FN(love_graphics_pop),
    DEF_FN(love_graphics_clear),
    DEF_FN(love_graphics_draw),
    DEF_FN(love_graphics_getWidth),
    DEF_FN(love_graphics_getHeight),
    DEF_FN(love_graphics_reset),
    DEF_FN(love_graphics_setColorMask),
    DEF_FN(love_graphics_getColorMask),
    DEF_FN(love_graphics_shear),
    DEF_FN(love_graphics_origin),
    DEF_FN(love_graphics_rotate),
    DEF_FN(love_graphics_scale),
    DEF_FN(love_graphics_setBlendMode),
    DEF_FN(love_graphics_getBlendMode),
    DEF_FN(love_graphics_setScissor),
    DEF_FN(love_graphics_getScissor),
    DEF_FN(love_graphics_translate),
    DEF_FN(love_graphics_getMaxAnisotropy),
    DEF_FN(love_graphics_getDPIScale),
};

void fh_graphics_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
