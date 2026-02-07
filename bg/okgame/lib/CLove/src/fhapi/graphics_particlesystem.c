/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "graphics_particlesystem.h"

#include "../include/particlesystem.h"

#include "../3rdparty/FH/src/value.h"

#include "image.h"
#include "graphics_quad.h"

fh_c_obj_gc_callback particle_gc(graphics_ParticleSystem *p) {
    graphics_ParticleSystem_free(p);
    free(p);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_graphics_newParticleSystem(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {

    if (!fh_is_c_obj_of_type(&args[0], FH_IMAGE_TYPE))
        return fh_set_error(prog, "Expected image");

    fh_image_t *image = fh_get_c_obj_value(&args[0]);

    double buffer = fh_optnumber(&args[1], n_args, 1, 128);

    graphics_ParticleSystem *p = malloc(sizeof(graphics_ParticleSystem));
    graphics_ParticleSystem_new(p, image->img, (size_t)buffer);

    fh_c_obj_gc_callback *callback = particle_gc;
    *ret = fh_new_c_obj(prog, p, callback, FH_GRAPHICS_PARTICLE);

    return 0;
}

static int fn_love_particleSystem_clone(struct fh_program *prog,
                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_c_obj_of_type(&args[1], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected two particle systems");

    graphics_ParticleSystem *cloned = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem *to = fh_get_c_obj_value(&args[1]);

    graphics_ParticleSystem_clone(cloned, to);

    *ret = fh_new_c_obj(prog, to, NULL, FH_GRAPHICS_PARTICLE);
    return 0;
}

static int fn_love_particleSystem_setLinearDamping(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1])
            || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle a min and a max");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float min = (float)fh_get_number(&args[1]);
    float max = (float)fh_get_number(&args[2]);

    graphics_ParticleSystem_setLinearDamping(p, min, max);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getLinearDamping(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getLinearDamping(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

static int fn_love_particleSystem_setBufferSize(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle and a size");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    int size = (int)fh_get_number(&args[1]);

    graphics_ParticleSystem_setBufferSize(p, size);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getBufferSize(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);

    *ret = fh_new_number(graphics_ParticleSystem_getBufferSize(p));
    return 0;
}

static int fn_love_particleSystem_setAreaSpread(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_string(&args[1])
            || !fh_is_number(&args[2])
            || !fh_is_number(&args[3]))
        return fh_set_error(prog, "Expected particle a mode:string, dx:number and a dy:number");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    const char *mode_str = fh_get_string(&args[1]);
    float dx = (float)fh_get_number(&args[2]);
    float dy = (float)fh_get_number(&args[3]);

    graphics_AreaSpreadDistribution mode;

    if (strcmp(mode_str, "uniform") == 0) {
        mode = graphics_AreaSpreadDistribution_uniform;
    } else if (strcmp(mode_str, "normal") == 0) {
        mode = graphics_AreaSpreadDistribution_normal;
    } else if (strcmp(mode_str, "none") == 0) {
        mode = graphics_AreaSpreadDistribution_none;
    } else {
        return fh_set_error(prog, "Invalid area spread distribution mode '%s'", mode_str);
    }

    graphics_ParticleSystem_setAreaSpread(p, mode, dx, dy);

    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getAreaSpread(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    float dx, dy;
    graphics_AreaSpreadDistribution mode;

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getAreaSpread(p, &mode, &dx, &dy);

    const char *mode_str;
    switch (mode) {
    case graphics_AreaSpreadDistribution_none:
        mode_str = "none";
        break;
    case graphics_AreaSpreadDistribution_normal:
        mode_str = "normal";
        break;
    case graphics_AreaSpreadDistribution_uniform:
        mode_str = "uniform";
        break;
    }

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 3))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_string(prog, mode_str);
    ret_arr->items[1] = fh_new_number((double)dx);
    ret_arr->items[2] = fh_new_number((double)dy);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

static int fn_love_particleSystem_setColors(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected particle and an array");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);

    struct fh_array *arr = GET_VAL_ARRAY(&args[1]);
    if (arr->len % 4 != 0)
        return fh_set_error(prog, "Array of colors must be power of 4");

    uint32_t len = arr->len / 4;
    graphics_Color *color = malloc(sizeof(graphics_Color) * len);
    if (!color) {
        return 0;
    }

    for (uint32_t i = 0; i < len; i++) {
        uint32_t value_index = i * 4;
        color[i].red = (float)fh_get_number(&arr->items[value_index]);
        color[i].green = (float)fh_get_number(&arr->items[value_index + 1]);
        color[i].blue = (float)fh_get_number(&arr->items[value_index + 2]);
        color[i].alpha = (float)fh_get_number(&arr->items[value_index + 3]);
    }

    graphics_ParticleSystem_setColors(p, len, color);

    free(color);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getColors(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    size_t count;

    graphics_Color const *color = graphics_ParticleSystem_getColors(p, &count);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, count * 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    for (uint32_t i = 0; i < count; i++) {
        uint32_t key_index = i * 4;
        ret_arr->items[key_index  + 0] = fh_new_number((double)color[i].red);
        ret_arr->items[key_index  + 1] = fh_new_number((double)color[i].green);
        ret_arr->items[key_index  + 2] = fh_new_number((double)color[i].blue);
        ret_arr->items[key_index  + 3] = fh_new_number((double)color[i].alpha);
    }

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getCount(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getCount(p));

    return 0;
}

static int fn_love_particleSystem_setDirection(struct fh_program *prog,
                                               struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle and number");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float dir = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setDirection(p, dir);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setEmissionRate(struct fh_program *prog,
                                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setEmissionRate(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setEmitterLifetime(struct fh_program *prog,
                                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setEmitterLifetime(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setSizeVariation(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setSizeVariation(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setSpinVariation(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setSpinVariation(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setSpread(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_setSpread(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getDirection(struct fh_program *prog,
                                               struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getDirection(p));

    return 0;
}

static int fn_love_particleSystem_getEmissionRate(struct fh_program *prog,
                                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getEmissionRate(p));

    return 0;
}

static int fn_love_particleSystem_getEmitterLifetime(struct fh_program *prog,
                                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getEmitterLifetime(p));

    return 0;
}

static int fn_love_particleSystem_getSizeVariation(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getSizeVariation(p));

    return 0;
}

static int fn_love_particleSystem_getSpinVariation(struct fh_program *prog,
                                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getSpinVariation(p));

    return 0;
}

static int fn_love_particleSystem_getSpread(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_number((double)graphics_ParticleSystem_getSpread(p));

    return 0;
}

static int fn_love_particleSystem_setOffset(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setOffset(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setPosition(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setPosition(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setRadialAcceleration(struct fh_program *prog,
                                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setRadialAcceleration(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setRotation(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setRotation(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setSpeed(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setSpeed(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setSpin(struct fh_program *prog,
                                          struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setSpin(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setTangentialAcceleration(struct fh_program *prog,
                                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_setTangentialAcceleration(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getOffset(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getOffset(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

static int fn_love_particleSystem_getParticleLifetime(struct fh_program *prog, struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getParticleLifetime(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getPosition(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getPosition(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getRadialAcceleration(struct fh_program *prog,
                                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getRadialAcceleration(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getRotation(struct fh_program *prog,
                                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getRotation(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;
    return 0;
}

static int fn_love_particleSystem_getSpeed(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getSpeed(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getSpin(struct fh_program *prog,
                                          struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getSpin(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_getTangentialAcceleration(struct fh_program *prog,
                                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float min, max;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getTangentialAcceleration(p, &min, &max);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 2))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)min);
    ret_arr->items[1] = fh_new_number((double)max);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

static int fn_love_particleSystem_setTexture(struct fh_program *prog,
                                             struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_c_obj_of_type(&args[1], FH_IMAGE_TYPE))
        return fh_set_error(prog, "Expected particle and a texture");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    fh_image_t *x = fh_get_c_obj_value(&args[1]);
    graphics_ParticleSystem_setTexture(p, x->img);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getTexture(struct fh_program *prog,
                                             struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    fh_image_t *x = malloc(sizeof(fh_image_t));
    x->img = graphics_ParticleSystem_getTexture(p);
    // We don't have to free the texture from the particle system that
    // we just fetched because it's just a reference, the object itself has its own life events
    *ret = fh_new_c_obj(prog, x, NULL, FH_IMAGE_TYPE);
    return 0;
}

static int fn_love_particleSystem_setSizes(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected particle and an array");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);

    struct fh_array *arr = GET_VAL_ARRAY(&args[1]);

    float *sizes = malloc(sizeof(float) * arr->len);

    for (uint32_t i = 0; i < arr->len; i++) {
        sizes[i] = (float)fh_get_number(&arr->items[i * 4 + 0]);
    }

    graphics_ParticleSystem_setSizes(p, arr->len, sizes);

    free(sizes);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getSizes(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    size_t count;

    float const *sizes = graphics_ParticleSystem_getSizes(p, &count);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, count))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    for (uint32_t i = 0; i < count; i++) {
        ret_arr->items[i] = fh_new_number((double)sizes[i]);
    }

    new_val.data.obj = ret_arr;
    *ret = new_val;
    fh_restore_pin_state(prog, pin_state);
    return 0;
}

static int fn_love_particleSystem_setQuads(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) || !fh_is_array(&args[1]))
        return fh_set_error(prog, "Expected particle and an array");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);

    struct fh_array *arr = GET_VAL_ARRAY(&args[1]);

    graphics_Quad **quads = malloc(sizeof(graphics_Quad) * arr->len);

    for (uint32_t i = 0; i < arr->len; i++) {
        if (fh_is_c_obj_of_type(&arr->items[i], FH_GRAPHICS_QUAD))
            return fh_set_error(prog, "Expected quad");
        quads[i] = fh_get_c_obj_value(&arr->items[i]);
    }

    graphics_ParticleSystem_setQuads(p, arr->len, quads);

    free(quads);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setRelativeRotation(struct fh_program *prog,
                                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) ||
            !fh_is_bool(&args[1]))
        return fh_set_error(prog, "Expected particle and boolean");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    bool v = fh_get_bool(&args[1]);

    graphics_ParticleSystem_setRelativeRotation(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_hasRelativeRotation(struct fh_program *prog,
                                                      struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_bool(graphics_ParticleSystem_hasRelativeRotation(p));
    return 0;
}

static int fn_love_particleSystem_setInsertMode(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) ||
            !fh_is_string(&args[1]))
        return fh_set_error(prog, "Expected particle and string");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    const char *v = fh_get_string(&args[1]);

    graphics_ParticleInsertMode mode;

    if (strcmp(v, "top") == 0) {
        mode = graphics_ParticleInsertMode_top;
    } else if (strcmp(v, "bottom") == 0) {
        mode = graphics_ParticleInsertMode_bottom;
    } else if (strcmp(v, "random") == 0) {
        mode = graphics_ParticleInsertMode_random;
    } else {
        return fh_set_error(prog, "Invalid mode '%s', expected: top, bottom or random", v);
    }
    graphics_ParticleSystem_setInsertMode(p, mode);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getInsertMode(struct fh_program *prog,
                                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);

    graphics_ParticleInsertMode mode = graphics_ParticleSystem_getInsertMode(p);

    switch (mode) {
    case graphics_ParticleInsertMode_top: {
        *ret = fh_new_string(prog, "top");
        break;
    }
    case graphics_ParticleInsertMode_bottom: {
        *ret = fh_new_string(prog, "bottom");
        break;
    }
    case graphics_ParticleInsertMode_random: {
        *ret = fh_new_string(prog, "random");
        break;
    }
    }

    return 0;
}

static int fn_love_particleSystem_isActive(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_bool(graphics_ParticleSystem_isActive(p));
    return 0;
}

static int fn_love_particleSystem_isPaused(struct fh_program *prog,
                                           struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_bool(graphics_ParticleSystem_isPaused(p));
    return 0;
}

static int fn_love_particleSystem_isStopped(struct fh_program *prog,
                                            struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    *ret = fh_new_bool(graphics_ParticleSystem_isStopped(p));
    return 0;
}

static int fn_love_particleSystem_moveTo(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE)
            || !fh_is_number(&args[1]) || !fh_is_number(&args[2]))
        return fh_set_error(prog, "Expected particle and two number values");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    graphics_ParticleSystem_moveTo(p, x, y);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_emit(struct fh_program *prog,
                                       struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) ||
            !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle and number");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float v = (float) fh_get_number(&args[1]);

    graphics_ParticleSystem_emit(p, v);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_start(struct fh_program *prog,
                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_start(p);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_stop(struct fh_program *prog,
                                       struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_stop(p);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_reset(struct fh_program *prog,
                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_reset(p);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_pause(struct fh_program *prog,
                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_pause(p);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_update(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) ||
            !fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected particle and dt");

    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float dt = (float)fh_get_number(&args[1]);
    graphics_ParticleSystem_update(p, dt);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_setLinearAcceleration(struct fh_program *prog,
                                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE) ||
            !fh_is_number(&args[1]) || !fh_is_number(&args[2])
            || !fh_is_number(&args[3]) || !fh_is_number(&args[4]))
        return fh_set_error(prog, "Expected particle, xmin, ymin, xmax and ymax");
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    float xmin = (float)fh_get_number(&args[1]);
    float ymin = (float)fh_get_number(&args[2]);
    float xmax = (float)fh_get_number(&args[3]);
    float ymax = (float)fh_get_number(&args[4]);

    graphics_ParticleSystem_setLinearAcceleration(p, xmin, ymin, xmax, ymax);
    *ret = fh_new_null();
    return 0;
}

static int fn_love_particleSystem_getLinearAcceleration(struct fh_program *prog,
                                                        struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_c_obj_of_type(&args[0], FH_GRAPHICS_PARTICLE))
        return fh_set_error(prog, "Expected particle");
    float xmin, ymin, xmax, ymax;
    graphics_ParticleSystem *p = fh_get_c_obj_value(&args[0]);
    graphics_ParticleSystem_getLinearAcceleration(p, &xmin, &ymin, &xmax, &ymax);

    int pin_state = fh_get_pin_state(prog);
    struct fh_array *ret_arr = fh_make_array(prog, true);
    if (!fh_grow_array_object(prog, ret_arr, 4))
        return fh_set_error(prog, "out of memory");

    struct fh_value new_val = fh_new_array(prog);

    ret_arr->items[0] = fh_new_number((double)xmin);
    ret_arr->items[1] = fh_new_number((double)ymin);
    ret_arr->items[2] = fh_new_number((double)xmax);
    ret_arr->items[3] = fh_new_number((double)ymax);

    fh_restore_pin_state(prog, pin_state);
    new_val.data.obj = ret_arr;
    *ret = new_val;

    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_graphics_newParticleSystem),
    DEF_FN(love_particleSystem_clone),
    DEF_FN(love_particleSystem_setLinearDamping),
    DEF_FN(love_particleSystem_getLinearDamping),
    DEF_FN(love_particleSystem_setBufferSize),
    DEF_FN(love_particleSystem_getBufferSize),
    DEF_FN(love_particleSystem_setAreaSpread),
    DEF_FN(love_particleSystem_getAreaSpread),
    DEF_FN(love_particleSystem_setColors),
    DEF_FN(love_particleSystem_getColors),
    DEF_FN(love_particleSystem_getCount),
    DEF_FN(love_particleSystem_setDirection),
    DEF_FN(love_particleSystem_setEmitterLifetime),
    DEF_FN(love_particleSystem_setSizeVariation),
    DEF_FN(love_particleSystem_setSpinVariation),
    DEF_FN(love_particleSystem_setSpread),
    DEF_FN(love_particleSystem_getDirection),
    DEF_FN(love_particleSystem_setEmissionRate),
    DEF_FN(love_particleSystem_getEmissionRate),
    DEF_FN(love_particleSystem_getEmitterLifetime),
    DEF_FN(love_particleSystem_getSizeVariation),
    DEF_FN(love_particleSystem_getSpinVariation),
    DEF_FN(love_particleSystem_getSpread),
    DEF_FN(love_particleSystem_setOffset),
    DEF_FN(love_particleSystem_setPosition),
    DEF_FN(love_particleSystem_setRadialAcceleration),
    DEF_FN(love_particleSystem_setRotation),
    DEF_FN(love_particleSystem_setSpeed),
    DEF_FN(love_particleSystem_getOffset),
    DEF_FN(love_particleSystem_getParticleLifetime),
    DEF_FN(love_particleSystem_getPosition),
    DEF_FN(love_particleSystem_getRadialAcceleration),
    DEF_FN(love_particleSystem_getRotation),
    DEF_FN(love_particleSystem_getSpeed),
    DEF_FN(love_particleSystem_setTangentialAcceleration),
    DEF_FN(love_particleSystem_getTangentialAcceleration),
    DEF_FN(love_particleSystem_setSpin),
    DEF_FN(love_particleSystem_getSpin),
    DEF_FN(love_particleSystem_getSizes),
    DEF_FN(love_particleSystem_setTexture),
    DEF_FN(love_particleSystem_getTexture),
    DEF_FN(love_particleSystem_setQuads),
    DEF_FN(love_particleSystem_setRelativeRotation),
    DEF_FN(love_particleSystem_hasRelativeRotation),
    DEF_FN(love_particleSystem_setInsertMode),
    DEF_FN(love_particleSystem_getInsertMode),
    DEF_FN(love_particleSystem_isActive),
    DEF_FN(love_particleSystem_isPaused),
    DEF_FN(love_particleSystem_isStopped),
    DEF_FN(love_particleSystem_moveTo),
    DEF_FN(love_particleSystem_emit),
    DEF_FN(love_particleSystem_start),
    DEF_FN(love_particleSystem_reset),
    DEF_FN(love_particleSystem_stop),
    DEF_FN(love_particleSystem_pause),
    DEF_FN(love_particleSystem_update),
    DEF_FN(love_particleSystem_setLinearAcceleration),
    DEF_FN(love_particleSystem_getLinearAcceleration),
};

void fh_graphics_particlesystem_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
