#include "../include/pc/hal.h"
#include <stdio.h>

// Stubs for HAL functions to avoid linking SDL2 in unit tests

uint64_t HAL_GetTimeMillis(void) {
    return 0; // Time is frozen in tests
}

void HAL_Delay(uint32_t millis) {
    (void)millis;
}

void HAL_Input_Poll(void) {}
void HAL_Input_GetState(int controller_index, OSContPad* pad) {
    (void)controller_index;
    (void)pad;
}

bool HAL_Video_Init(VideoConfig* config) { (void)config; return true; }
void HAL_Video_Shutdown(void) {}
void HAL_Video_BeginFrame(void) {}
void HAL_Video_EndFrame(void) {}
void HAL_Video_SetFullscreen(bool enabled) { (void)enabled; }

bool HAL_Audio_Init(AudioConfig* config) { (void)config; return true; }
void HAL_Audio_Shutdown(void) {}
void HAL_Audio_QueueSamples(const int16_t* samples, int count) { (void)samples; (void)count; }
