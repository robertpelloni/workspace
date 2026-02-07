#include "pc/hal.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;

    printf("F-Zero X PC Port (Shell)\n");

    VideoConfig videoConfig = {
        .width = 640,
        .height = 480,
        .fullscreen = false,
        .title = "F-Zero X (Decompilation)"
    };

    if (!HAL_Video_Init(&videoConfig)) {
        printf("Failed to init video.\n");
        return 1;
    }

    AudioConfig audioConfig = {
        .frequency = 44100,
        .channels = 2,
        .samples = 1024
    };

    if (!HAL_Audio_Init(&audioConfig)) {
        printf("Failed to init audio.\n");
        HAL_Video_Shutdown();
        return 1;
    }

    printf("Initialization successful. Running main loop...\n");

    bool running = true;
    OSContPad pad;

    while (running) {
        HAL_Input_Poll();
        HAL_Input_GetState(0, &pad);

        if (pad.button & CONT_A) {
            printf("Button A Pressed!\n");
        }

        HAL_Video_BeginFrame();
        // TODO: Call Game Render Loop Here
        HAL_Video_EndFrame();

        // Limit FPS (simple delay)
        HAL_Delay(16);
    }

    HAL_Audio_Shutdown();
    HAL_Video_Shutdown();
    return 0;
}
