/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include <stdlib.h>

#include "../include/stb_vorbis.h"
#include "../include/vorbis_decoder.h"
#include "../include/utils.h"


int audio_vorbis_load(ALuint buffer, char const *filename) {
  short *data;
  int channels;
  int samplingrate;
  int len = stb_vorbis_decode_filename(filename, &channels, &samplingrate, &data);

  if(len == -1) {
      clove_error("%s %s \n", "Error in loading ", filename);
      return 0;
    }

  //printf("%s %d %d %d %d \n", "Data: ", buffer, channels, len, samplingrate);

  alBufferData(buffer, channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16, data,
               len * sizeof(ALshort) * channels, samplingrate);

  free(data);
  return 1;
}

int audio_vorbis_loadStream(audio_vorbis_DecoderData* data, char const *filename) {
  int err;
  data->vorbis = stb_vorbis_open_filename(filename, &err, NULL);

  data->info = stb_vorbis_get_info(data->vorbis);

  data->readBufferSize    = data->info.channels * data->info.sample_rate + 4069;
  data->readBuffer        = malloc(sizeof(ALshort) * data->readBufferSize);
  data->preloadedSamples  = 0;
  return err;
}

int audio_vorbis_preloadStreamSamples(audio_vorbis_DecoderData *data, int sampleCount) {
  int channels = data->info.channels >= 2 ? 2 : 1;   // Force to mono or stereo

  int safeBufferSize = sampleCount * channels + 4069;
  if(safeBufferSize > data->readBufferSize) {
      data->readBufferSize = safeBufferSize;
      free(data->readBuffer);
      data->readBuffer = malloc(sizeof(ALshort) * safeBufferSize);
    }

  int space = data->readBufferSize - data->preloadedSamples - 4069;

  if(space <= 0) {
      //printf("Buffer already 100%% filled, no need to read more\n");
      return -1;
    }

  if(space < sampleCount) {
      sampleCount = space;
    }

  int readSamples = 0;
  while(readSamples < sampleCount) {
      float **channelData;
      int samples = stb_vorbis_get_frame_float(data->vorbis, NULL, &channelData);
      if(samples == 0)
       break;
      for(int i = 0; i < samples; ++i) {
          for(int c = 0; c < channels; ++c) {
              data->readBuffer[data->preloadedSamples + readSamples + channels * i + c] = (channelData[c][i] * 32767);
            }
        }

      readSamples += channels * samples;
    }

  data->preloadedSamples += readSamples;
  //printf("Preloaded %d samples, buffered: %d samples\n", readSamples, data->preloadedSamples);

  return readSamples;
}

int audio_vorbis_uploadSreamSamples(audio_vorbis_DecoderData *data, ALuint buffer) {
  int channels = data->info.channels >= 2 ? 2 : 1;   // Force to mono or stereo

  // Emergency loading if we ran out of time for proper preloading
  if(data->preloadedSamples < data->readBufferSize / 2) {
      audio_vorbis_preloadStreamSamples(data, data->readBufferSize / 2);
    }


  //printf("uploaded %d samples to buffer %d\n", data->preloadedSamples, buffer);
  alBufferData(
        buffer,
        channels == 2 ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16,
        data->readBuffer,
        data->preloadedSamples * sizeof(ALshort),
        data->info.sample_rate
        );
  int uploaded = data->preloadedSamples;
  data->preloadedSamples = 0;
  return uploaded;
}

void audio_vorbis_rewindStream(audio_vorbis_DecoderData *decoderData) {
  audio_vorbis_DecoderData * data = (audio_vorbis_DecoderData*)decoderData;
  stb_vorbis_seek_start(data->vorbis);
}

int audio_vorbis_getChannelCount(audio_vorbis_DecoderData *data) {
  return data->info.channels;
}

int audio_vorbis_getSampleRate(audio_vorbis_DecoderData *data) {
  return data->info.sample_rate;
}

void audio_vorbis_flushBuffer(audio_vorbis_DecoderData *decoderData) {
  audio_vorbis_DecoderData * data = (audio_vorbis_DecoderData*)decoderData;
  data->preloadedSamples = 0;
}
