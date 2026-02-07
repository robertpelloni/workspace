#include "pc/hal.h"
#include <SDL2/SDL.h>

uint64_t HAL_GetTimeMillis(void) {
    return SDL_GetTicks64();
}

void HAL_Delay(uint32_t millis) {
    SDL_Delay(millis);
}
