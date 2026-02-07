/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include <stdbool.h>

#include "stb_vorbis.h"

#include "audio.h"
#include "source.h"

typedef struct {
    stb_vorbis *vorbis;
    ALshort    *readBuffer;
    stb_vorbis_info info;
    int         readBufferSize;
    int         preloadedSamples;
} audio_vorbis_DecoderData;

typedef struct {
    audio_vorbis_DecoderData* decoderData;
    audio_SourceState state;
    bool loop;
    int channels;
    int sampleRate;
    ALuint source;
    ALuint buffers[6];
    int maxFrameSamples;
    int samplesRead;
    int nextBuffer;
} audio_StreamSource;

void audio_updateStreams(void);
void audio_StreamInit(void);
int audio_loadStream(audio_StreamSource* source, char const* filename);
void audio_StreamSource_stop(audio_StreamSource* source);
void audio_StreamSource_play(audio_StreamSource* source);
void audio_StreamSource_pause(audio_StreamSource *source);
void audio_StreamSource_resume(audio_StreamSource *source);
bool audio_StreamSource_isLooping(audio_StreamSource* source);
bool audio_StreamSource_isPlaying(audio_StreamSource* source);
bool audio_StreamSource_isStopped(audio_StreamSource* source);
bool audio_StreamSource_isPaused(audio_StreamSource* source);
void audio_StreamSource_setVolume(audio_StreamSource* source, float gain);
float audio_StreamSource_getVolume(audio_StreamSource* source);
float audio_StreamSource_getPitch(audio_StreamSource* source);
void audio_StreamSource_setPitch(audio_StreamSource* source, float gain);
void audio_StreamSource_setPosition(audio_StreamSource* source, float x, float y, float z);
void audio_StreamSource_setVelocity(audio_StreamSource* source, float x, float y, float z);
void audio_StreamSource_setLooping(audio_StreamSource* source, int value);
void audio_StreamSource_free(audio_StreamSource* source);
