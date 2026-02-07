#include "pc/hal.h"
#include <SDL2/SDL.h>
#include <string.h>

static OSContPad sControllerState[4];

void HAL_Input_Poll(void) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0); // Simple exit for now
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    OSContPad* pad = &sControllerState[0];

    // Reset state
    memset(pad, 0, sizeof(OSContPad));

    // D-Pad / Analog Stick Mapping (Arrow Keys)
    if (state[SDL_SCANCODE_UP])    pad->stick_y = 127;
    if (state[SDL_SCANCODE_DOWN])  pad->stick_y = -127;
    if (state[SDL_SCANCODE_LEFT])  pad->stick_x = -127;
    if (state[SDL_SCANCODE_RIGHT]) pad->stick_x = 127;

    // Buttons (Z, X, C, Enter)
    if (state[SDL_SCANCODE_Z])      pad->button |= CONT_A;
    if (state[SDL_SCANCODE_X])      pad->button |= CONT_B;
    if (state[SDL_SCANCODE_RETURN]) pad->button |= CONT_START;

    // Shoulder Triggers
    if (state[SDL_SCANCODE_A])      pad->button |= CONT_L; // 'A' key for L trigger
    if (state[SDL_SCANCODE_S])      pad->button |= CONT_R; // 'S' key for R trigger
    if (state[SDL_SCANCODE_D])      pad->button |= CONT_Z; // 'D' key for Z trigger (Wait, CONT_Z?)
}

void HAL_Input_GetState(int controller_index, OSContPad* pad) {
    if (controller_index >= 0 && controller_index < 4) {
        *pad = sControllerState[controller_index];
    } else {
        memset(pad, 0, sizeof(OSContPad));
    }
}
