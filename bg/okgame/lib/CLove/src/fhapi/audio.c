/*
#   clove
#
#   Copyright (C) 2019-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "audio.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/vector.h" // for CLAMP
#include "../include/audio.h"
#include "../include/staticsource.h"
#include "../include/streamsource.h"

static fh_c_obj_gc_callback gcStaticSource(audio_StaticSource *source) {
    audio_SourceCommon_free(&source->common);
    audio_StaticSource_free(source);
    free(source);
    return (fh_c_obj_gc_callback)1;
}


static fh_c_obj_gc_callback gcStreamSource(audio_StreamSource *source) {
    audio_StreamSource_free(source);
    free(source);
    return (fh_c_obj_gc_callback)1;
}

static int fn_love_audio_newSource(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_string(&args[0]))
        return fh_set_error(prog, "Expected string as filename");

    const char *filename = fh_get_string(&args[0]);
    const char *type = fh_optstring(args, n_args, 1, "static");
    int err = 1;
    audio_StaticSource *staticSource = NULL;
    audio_StreamSource *streamSource = NULL;
    if (strcmp(type, "static") == 0) {
        fh_c_obj_gc_callback *callback = gcStaticSource;

        staticSource = malloc(sizeof(audio_StaticSource));
        err = audio_loadStatic(staticSource, filename);
        if (err == 1) {
            *ret = fh_new_c_obj(prog, staticSource, callback, FH_AUDIO_STATIC_SOURCE_TYPE);
        } else {
            free(staticSource);
        }
    } else if (strcmp(type, "stream") == 0) {
        fh_c_obj_gc_callback *callback = gcStreamSource;

        streamSource = malloc(sizeof(audio_StreamSource));
        err = audio_loadStream(streamSource, filename);
        if (err == 1) {
            *ret = fh_new_c_obj(prog, streamSource, callback, FH_AUDIO_STREAM_SOURCE_TYPE);
        } else {
            free(streamSource);
        }
    }
    if (err != 1) {
        if (err == 0) {
            return fh_set_error(prog, "Could not load sound file %s, file does not exist", filename);
        }
        return fh_set_error(prog, "Could not load sound file %s, reason: unknown file type", filename);
    }
    return 0;
}

static int fn_love_audio_play(struct fh_program *prog,
                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_StaticSource_play(source);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_play(source);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_getType(struct fh_program *prog,
                                 struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        *ret = fh_new_string(prog, "static");
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        *ret = fh_new_string(prog, "stream");
    }
    else
        return fh_set_error(prog, "Expected audio source object");

    return 0;
}

static int fn_love_audio_stop(struct fh_program *prog,
                              struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_StaticSource_stop(source);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_stop(source);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_pause(struct fh_program *prog,
                               struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_StaticSource_pause(source);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_pause(source);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    *ret = fh_new_null();
    return 0;
}


static int fn_love_audio_resume(struct fh_program *prog,
                                struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_StaticSource_play(source);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_play(source);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    *ret = fh_new_null();
    return 0;
}


static int fn_love_audio_isStopped(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_SourceCommon_isStopped(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_StreamSource_isStopped(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    return 0;
}

static int fn_love_audio_isPlaying(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_SourceCommon_isPlaying(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_StreamSource_isPlaying(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    return 0;
}


static int fn_love_audio_isPaused(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_SourceCommon_isPaused(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_StreamSource_isPaused(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    return 0;
}


static int fn_love_audio_setVolume(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 2)
        return fh_set_error(prog, "Illegal number of arguments, expected two arguments");

    if (!fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected volume:number for the seecond argument");

    float volume = (float)fh_get_number(&args[1]);

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_SourceCommon_setVolume(&source->common, volume);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_setVolume(source, volume);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_getVolume(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number(audio_SourceCommon_getVolume(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number(audio_StreamSource_getVolume(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    return 0;
}

static int fn_love_audio_setPitch(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 2)
        return fh_set_error(prog, "Illegal number of arguments, expected two arguments");

    if (!fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected pitch:number for the seecond argument");

    float pitch = (float)fh_get_number(&args[1]);

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_SourceCommon_setPitch(&source->common, pitch);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_setPitch(source, pitch);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_getPitch(struct fh_program *prog,
                                  struct fh_value *ret, struct fh_value *args, int n_args) {

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number(audio_SourceCommon_getPitch(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_number(audio_StreamSource_getPitch(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    return 0;
}

static int fn_love_audio_setLooping(struct fh_program *prog,
                                    struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 2)
        return fh_set_error(prog, "Illegal number of arguments, expected two arguments");

    if (!fh_is_bool(&args[1]))
        return fh_set_error(prog, "Expected looping:bool for the seecond argument");

    bool looping = fh_get_bool(&args[1]);

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_SourceCommon_setLooping(&source->common, looping);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_setLooping(source, looping);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_isLooping(struct fh_program *prog,
                                   struct fh_value *ret, struct fh_value *args, int n_args) {

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_SourceCommon_isLooping(&source->common));
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        *ret = fh_new_bool(audio_StreamSource_isLooping(source));
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");

    return 0;
}

static int fn_love_audio_setVelocity(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 4)
        return fh_set_error(prog, "Illegal number of arguments, expected four arguments");

    if (!fh_is_number(&args[1]) || !fh_is_number(&args[2]) || !fh_is_number(&args[3]))
        return fh_set_error(prog, "Expected three numbers, x, y and z");

    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    float z = (float)fh_get_number(&args[3]);

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_SourceCommon_setVelocity(&source->common, x, y, z);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_setVelocity(source, x, y, z);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_setPosition(struct fh_program *prog,
                                     struct fh_value *ret, struct fh_value *args, int n_args) {
    if (n_args != 4)
        return fh_set_error(prog, "Illegal number of arguments, expected four arguments");

    if (!fh_is_number(&args[1]) || !fh_is_number(&args[2]) || !fh_is_number(&args[3]))
        return fh_set_error(prog, "Expected three numbers, x, y and z");

    float x = (float)fh_get_number(&args[1]);
    float y = (float)fh_get_number(&args[2]);
    float z = (float)fh_get_number(&args[3]);

    if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STATIC_SOURCE_TYPE)) {
        audio_StaticSource *source = fh_get_c_obj_value(&args[0]);
        audio_SourceCommon_setPosition(&source->common, x, y, z);
    } else if (fh_is_c_obj_of_type(&args[0], FH_AUDIO_STREAM_SOURCE_TYPE)) {
        audio_StreamSource *source = fh_get_c_obj_value(&args[0]);
        audio_StreamSource_setPosition(source, x, y, z);
    }
    else
        return fh_set_error(prog, "Expected stream or static audio source");
    *ret = fh_new_null();
    return 0;
}

static int fn_love_audio_setGlobalVolume(struct fh_program *prog,
                                         struct fh_value *ret, struct fh_value *args, int n_args) {
    if (!fh_is_number(&args[1]))
        return fh_set_error(prog, "Expected volume:bool for the seecond argument");

    float volume = (float)fh_get_number(&args[1]);

    audio_setVolume(CLAMP(volume, 0.0f, 1.0f));
    *ret = fh_new_null();
    return 0;
}

#define DEF_FN(name) { #name, fn_##name }
static const struct fh_named_c_func c_funcs[] = {
    DEF_FN(love_audio_newSource),
    DEF_FN(love_audio_setGlobalVolume),
    DEF_FN(love_audio_play),
    DEF_FN(love_audio_pause),
    DEF_FN(love_audio_stop),
    DEF_FN(love_audio_resume),
    DEF_FN(love_audio_getType),
    DEF_FN(love_audio_isStopped),
    DEF_FN(love_audio_isPlaying),
    DEF_FN(love_audio_isPaused),
    DEF_FN(love_audio_isLooping),
    DEF_FN(love_audio_setVolume),
    DEF_FN(love_audio_getVolume),
    DEF_FN(love_audio_setPitch),
    DEF_FN(love_audio_getPitch),
    DEF_FN(love_audio_setLooping),
    DEF_FN(love_audio_setVelocity),
    DEF_FN(love_audio_setPosition),

};

void fh_audio_register(struct fh_program *prog) {
    fh_add_c_funcs(prog, c_funcs, sizeof(c_funcs)/sizeof(c_funcs[0]));
}
