/*
#   clove
#
#   Copyright (C) 2016-2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/mojoAL/AL/al.h"

#include <stdbool.h>

typedef enum {
  audio_type_stream,
  audio_type_static,
} audio_Type;

void audio_init(bool stats);
void audio_setVolume(float value);
void audio_close(void);
