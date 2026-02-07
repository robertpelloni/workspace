/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "audio.h"
#include "streamsource.h"

int audio_vorbis_load(ALuint buffer, char const *filename);
int audio_vorbis_loadStream(audio_vorbis_DecoderData* data, char const *filename);
int audio_vorbis_preloadStreamSamples(audio_vorbis_DecoderData* decoderData, int sampleCount);
int audio_vorbis_uploadSreamSamples(audio_vorbis_DecoderData* decoderData, ALuint buffer);
void audio_vorbis_rewindStream(audio_vorbis_DecoderData *decoderData);
int audio_vorbis_getChannelCount(audio_vorbis_DecoderData *decoderData);
int audio_vorbis_getSampleRate(audio_vorbis_DecoderData *decoderData);
void audio_vorbis_flushBuffer(audio_vorbis_DecoderData *decoderData);
