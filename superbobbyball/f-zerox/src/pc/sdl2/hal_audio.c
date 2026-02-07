#include "pc/hal.h"
#include <SDL2/SDL.h>
#include <stdio.h>

static SDL_AudioDeviceID sAudioDevice = 0;

bool HAL_Audio_Init(AudioConfig* config) {
    SDL_AudioSpec want, have;
    SDL_memset(&want, 0, sizeof(want));

    want.freq = config->frequency;
    want.format = AUDIO_S16SYS;
    want.channels = config->channels;
    want.samples = config->samples;
    want.callback = NULL; // We will use SDL_QueueAudio

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL Audio Init Failed: %s\n", SDL_GetError());
        return false;
    }

    sAudioDevice = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
    if (sAudioDevice == 0) {
        printf("Failed to open audio device: %s\n", SDL_GetError());
        return false;
    }

    SDL_PauseAudioDevice(sAudioDevice, 0); // Start playing
    return true;
}

void HAL_Audio_Shutdown(void) {
    if (sAudioDevice != 0) {
        SDL_CloseAudioDevice(sAudioDevice);
        sAudioDevice = 0;
    }
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

void HAL_Audio_QueueSamples(const int16_t* samples, int count) {
    if (sAudioDevice != 0) {
        // count is number of samples (int16), size in bytes is count * sizeof(int16)
        SDL_QueueAudio(sAudioDevice, samples, count * sizeof(int16_t));
    }
}
