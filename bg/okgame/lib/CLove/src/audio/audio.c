/*
#   clove
#
#   Copyright (C) 2016-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include <stdio.h>

#include "../3rdparty/mojoAL/AL/al.h"
#include "../3rdparty/mojoAL/AL/alc.h"

#include "../include/utils.h"
#include "../include/audio.h"
#include "../include/streamsource.h"

static struct {
	ALCdevice* device;
	ALCcontext* context;
} moduleData;

static int check_openal_alc_error(ALCdevice *device, const char *where)
{
    const ALCenum err = alcGetError(device);
    if (err != AL_NONE) {
        printf("ALC Error at %s! %s (%u)\n", where, alcGetString(device, err), (unsigned int) err);
        return 1;
    }
    return 0;
}

void audio_init(bool stats) {
	moduleData.device = alcOpenDevice(NULL);
    check_openal_alc_error(moduleData.device, "alcOpenDevice");
    if (!moduleData.device) {
        clove_error("Couldn't open OpenAL default device.\n");
        return;
    }
	moduleData.context = alcCreateContext(moduleData.device, NULL);
    check_openal_alc_error(moduleData.device, "alcCreateContext");
    if (!moduleData.context) {
        clove_error("Couldn't create OpenAL context.\n");
        alcCloseDevice(moduleData.device);
        return;
    }

    alcMakeContextCurrent(moduleData.context);
    check_openal_alc_error(moduleData.device, "alcMakeContextCurrent");

	audio_StreamInit();
    if (stats > 0) {
		clove_error("OpenAL version: %s\n", alGetString(AL_VERSION));
    }
}

void audio_setVolume(float value) {
	alListenerf(AL_GAIN, value);
}

void audio_close () {
	alcMakeContextCurrent(NULL);
    check_openal_alc_error(moduleData.device, "alcMakeContextCurrent(NULL)");
	alcDestroyContext(moduleData.context);
    check_openal_alc_error(moduleData.device, "alcDestroyContext");
	alcCloseDevice(moduleData.device);
    check_openal_alc_error(NULL, "alcCloseDevice");
}
