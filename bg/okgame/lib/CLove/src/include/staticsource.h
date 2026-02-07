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
#include "source.h"

typedef struct {
  audio_SourceCommon common;
  ALuint buffer;
  audio_Type audio_type;
} audio_StaticSource;


int audio_loadStatic(audio_StaticSource *source, char const * filename);
void audio_StaticSource_play(audio_StaticSource *source);
void audio_StaticSource_setLooping(audio_StaticSource *source, bool loop);
void audio_StaticSource_stop(audio_StaticSource *source);
void audio_StaticSource_rewind(audio_StaticSource *source);
void audio_StaticSource_pause(audio_StaticSource *source);
void audio_StaticSource_resume(audio_StaticSource *source);
void audio_StaticSource_free(audio_StaticSource *source);
