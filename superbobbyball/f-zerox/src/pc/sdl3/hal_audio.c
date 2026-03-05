#include "pc/hal.h"
#include <SDL3/SDL.h>
#include <stdio.h>

static SDL_AudioStream *sAudioStream = NULL;

bool HAL_Audio_Init(AudioConfig* config) {
    SDL_AudioSpec spec;
    SDL_memset(&spec, 0, sizeof(spec));

    spec.freq = config->frequency;
    spec.format = SDL_AUDIO_S16;
    spec.channels = config->channels;

    if (!SDL_Init(SDL_INIT_AUDIO)) {
        printf("SDL Audio Init Failed: %s\n", SDL_GetError());
        return false;
    }

    sAudioStream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!sAudioStream) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        return false;
    }

    SDL_ResumeAudioStreamDevice(sAudioStream); // Start playing
    return true;
}

void HAL_Audio_Shutdown(void) {
    if (sAudioStream != NULL) {
        SDL_DestroyAudioStream(sAudioStream);
        sAudioStream = NULL;
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void HAL_Audio_QueueSamples(const int16_t* samples, int count) {
    if (sAudioStream != NULL) {
        SDL_PutAudioStreamData(sAudioStream, samples, count * sizeof(int16_t));
    }
}
