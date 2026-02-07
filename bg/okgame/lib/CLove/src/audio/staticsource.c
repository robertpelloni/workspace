/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "../include/staticsource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"
// loaders
#include "../include/wav_decoder.h"
#include "../include/vorbis_decoder.h"

static int check_openal_error(const char *where)
{
    const ALenum err = alGetError();
    if (err != AL_NONE) {
        printf("OpenAL Error at %s! %s (%u)\n", where, alGetString(err), (unsigned int) err);
        return 1;
    }
    return 0;
}

static const char* get_filename_ext(const char *filename) {
	const char *dot = strrchr(filename, '.');
	if(!dot || dot == filename) return "";
	return dot+1;
}

int audio_loadStatic(audio_StaticSource *source, char const * filename) {
	audio_SourceCommon_init(&source->common);

	ALenum err; // openAL error checker.

	int loaded = 1; // error checker ;)
	memset(&source->buffer, 0, sizeof(ALuint));

	alGenBuffers(1, &source->buffer);
	err = alGetError();

    if (err != AL_NO_ERROR) {
		clove_error("Error: Could not generate openAL buffer \n");
		return 0;
	}

	if(strcmp(get_filename_ext(filename), "wav") == 0){
		loaded = audio_wav_load(source->buffer, filename);
	}else if((strcmp(get_filename_ext(filename), "ogg")) == 0){
		loaded = audio_vorbis_load(source->buffer, filename);
	}else
		return -1; //Unknow file type :(

	alSourcei(source->common.source, AL_BUFFER, source->buffer);

	return loaded;
}

void audio_StaticSource_play(audio_StaticSource *source) {
	if(source->common.state != audio_SourceState_playing) {
		audio_SourceCommon_play(&source->common);
	}
}

void audio_StaticSource_setLooping(audio_StaticSource *source, bool loop) {
	alSourcei(source->common.source, AL_LOOPING, loop);
}

void audio_StaticSource_stop(audio_StaticSource *source) {
	audio_SourceCommon_stop(&source->common);
	audio_StaticSource_rewind(source);
}

void audio_StaticSource_rewind(audio_StaticSource *source) {
	alSourceRewindv(1, &source->common.source);

	if(source->common.state == audio_SourceState_playing) {
		audio_SourceCommon_play(&source->common);
	}
}

void audio_StaticSource_pause(audio_StaticSource *source) {
	audio_SourceCommon_pause(&source->common);
}

void audio_StaticSource_resume(audio_StaticSource *source) {
	audio_SourceCommon_resume(&source->common);
}

void audio_StaticSource_free(audio_StaticSource *source) {
    alSourceUnqueueBuffers(source->common.source, 1, &source->buffer);
    alDeleteBuffers(1, &source->buffer);
    //check_openal_error("alDeleteBuffers");
}

