/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "graphics_batch.h"

#include <math.h>

#include "../3rdparty/FH/src/value.h"

#include "../include/batch.h"
#include "../include/quad.h"

#include "graphics_quad.h"
#include "image.h"

static fh_c_obj_gc_callback batch_gc(graphics_Batch *batch) {
    graphics_Batch_free(batch);
    free(batch);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_graphics_newSpriteBatch(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_IMAGE_TYPE)) {
        return fh_set_error(prog, "Expected image type");
    }
    fh_image_t *image = fh_get_c_obj_value(&args[0]);
    int count = (int)fh_optnumber(args, n_args, 1, 128);

    graphics_Batch *batch = malloc(sizeof(graphics_Batch));
    graphics_Batch_new(batch, image->img, count, graphics_BatchUsage_static);

    fh_c_obj_gc_callback *callback = batch_gc;
    *ret = fh_new_c_obj(prog, batch, callback, FH_GRAPHICS_BATCH);
    return 0;
}

static int fn_love_graphics_batch_bind(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    graphics_Batch_bind(batch);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_unbind(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    graphics_Batch_unbind(batch);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_flush(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    graphics_Batch_flush(batch);
    *ret = fh_new_null();
    return 0;
}

static const graphics_Quad defaultQuad = {
    .x = 0.0,
    .y = 0.0,
    .w = 1.0,
    .h = 1.0
};

static int fn_love_graphics_batch_add(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);

    graphics_Quad const *quad = &defaultQuad;
    int basedidx = 1;

    if (fh_is_c_obj_of_type(&args[1], FH_GRAPHICS_QUAD)) {
        quad = fh_get_c_obj_value(&args[1]);
        basedidx = 2;
    }

    float x = (float)fh_optnumber(args,  n_args, basedidx, 0.0);
    float y = (float)fh_optnumber(args,  n_args, basedidx + 1, 0.0);
    float r = (float)fh_optnumber(args,  n_args, basedidx + 2, 0.0);
    float sx = (float)fh_optnumber(args, n_args, basedidx + 3, 1.0);
    float sy = (float)fh_optnumber(args, n_args, basedidx + 4, 1.0);
    float ox = (float)fh_optnumber(args, n_args, basedidx + 5, 0.0);
    float oy = (float)fh_optnumber(args, n_args, basedidx + 6, 0.0);
    float kx = (float)fh_optnumber(args, n_args, basedidx + 7, 0.0);
    float ky = (float)fh_optnumber(args, n_args, basedidx + 8, 0.0);

    int i = graphics_Batch_add(batch, quad, x, y, r, sx, sy, ox, oy, kx, ky);
    *ret = fh_new_number(i);
    return 0;
}

static int fn_love_graphics_batch_set(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH) || !fh_is_number(&args[1])) {
        return fh_set_error(prog, "Expected spritebatch and id");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);

    int id = (int)fh_get_number(&args[1]);

    graphics_Quad const *quad = &defaultQuad;
    int basedidx = 2;

    /*if (fh_is_c_obj_of_type(&args[1], FH_GRAPHICS_QUAD)) {
        quad = fh_get_c_obj_value(&args[1]);
        basedidx = 3;
    }*/

    float x = (float)fh_optnumber(args, n_args, basedidx, 0.0);
    float y = (float)fh_optnumber(args, n_args, basedidx + 1, 0.0);
    float r = (float)fh_optnumber(args, n_args, basedidx + 2, 0.0);
    float sx = (float)fh_optnumber(args, n_args, basedidx + 3, 1.0);
    float sy = (float)fh_optnumber(args, n_args, basedidx + 4, sx);
    float ox = (float)fh_optnumber(args, n_args, basedidx + 5, 0.0);
    float oy = (float)fh_optnumber(args, n_args, basedidx + 6, 0.0);
    float kx = (float)fh_optnumber(args, n_args, basedidx + 7, 0.0);
    float ky = (float)fh_optnumber(args, n_args, basedidx + 8, 0.0);

    graphics_Batch_set(batch, id, quad, x, y, r, sx, sy, ox, oy, kx, ky);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_clear(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    graphics_Batch_clear(batch);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_getBufferSize(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number(batch->maxCount);
    return 0;
}

static int fn_love_graphics_batch_setBufferSize(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH) || !fh_is_number(&args[1])) {
        return fh_set_error(prog, "Expected spritebatch and new size:number");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    int newsize = (int)fh_get_number(&args[1]);
    graphics_Batch_changeBufferSize(batch, newsize);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_getCount(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number(batch->insertPos);
    return 0;
}

static int fn_love_graphics_batch_setTexture(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH) || !fh_is_c_obj_of_type(&args[1], FH_IMAGE_TYPE)) {
        return fh_set_error(prog, "Expected spritebatch and image");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);
    graphics_Image *image = fh_get_c_obj_value(&args[1]);

    batch->texture = image;

    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_getTexture(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);

    *ret = fh_new_c_obj(prog, batch->texture, NULL, FH_IMAGE_TYPE);
    return 0;

}

static int fn_love_graphics_batch_setColor(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);

    if (fh_is_null(&args[1])) {
        graphics_Batch_clearColor(batch);
    } else {
        for (int i = 1; i < 5; i++) {
            if (!fh_is_number(&args[i]))
                return fh_set_error(prog, "Expected r, g, b");
        }
        float r = (float)fh_get_number(&args[1]);
        float g = (float)fh_get_number(&args[2]);
        float b = (float)fh_get_number(&args[3]);
        float a = (float)fh_optnumber(args, n_args, 4, 1.0);
        graphics_Batch_setColor(batch, r, g, b, a);
    }

    *ret = fh_new_null();
    return 0;
}

static int fn_love_graphics_batch_getColor(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_BATCH)) {
        return fh_set_error(prog, "Expected spritebatch");
    }
    graphics_Batch *batch = fh_get_c_obj_value(&args[0]);

    if (!batch->colorSet) {
        *ret = fh_new_null();
        return 0;
    }

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number(floorf(batch->color.x * 255));
    ret_arr->items[1] = fh_new_number(floorf(batch->color.y * 255));
    ret_arr->items[2] = fh_new_number(floorf(batch->color.z * 255));
    ret_arr->items[3] = fh_new_number(floorf(batch->color.w * 255));

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newSpriteBatch),
    DEF_FN(love_graphics_batch_bind),
    DEF_FN(love_graphics_batch_unbind),
    DEF_FN(love_graphics_batch_flush),
    DEF_FN(love_graphics_batch_clear),
    DEF_FN(love_graphics_batch_getBufferSize),
    DEF_FN(love_graphics_batch_setBufferSize),
    DEF_FN(love_graphics_batch_getCount),
    DEF_FN(love_graphics_batch_add),
    DEF_FN(love_graphics_batch_set),
    DEF_FN(love_graphics_batch_setTexture),
    DEF_FN(love_graphics_batch_getTexture),
    DEF_FN(love_graphics_batch_setColor),
    DEF_FN(love_graphics_batch_getColor),
};

void fh_graphics_batch_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
