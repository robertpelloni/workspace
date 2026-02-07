/*
#   clove
#
#   Copyright (C) 2019-2025 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef USE_FH

#include "include/fh_mainactivity.h"

#include "3rdparty/FH/src/value.h"

#include "fhapi/keyboard.h"
#include "fhapi/mouse.h"
#include "fhapi/joystick.h"
#include "fhapi/timer.h"
#include "fhapi/graphics_geometry.h"
#include "fhapi/image.h"
#include "fhapi/graphics.h"
#include "fhapi/graphics_window.h"
#include "fhapi/math.h"
#include "fhapi/graphics_font.h"
#include "fhapi/graphics_bitmapfont.h"
#include "fhapi/filesystem.h"
#include "fhapi/audio.h"
#include "fhapi/graphics_batch.h"
#include "fhapi/event.h"
#include "fhapi/graphics_mesh.h"
#include "fhapi/graphics_quad.h"
#include "fhapi/graphics_shader.h"
#include "fhapi/graphics_particlesystem.h"
#include "fhapi/love.h"
#include "fhapi/ui.h"
#include "fhapi/graphics_canvas.h"
#include "fhapi/config.h"

#include "include/geometry.h"
#include "include/ui.h"

#include "../native/game.h"

// #define USE_NATIVE 1

typedef struct {
    bool called_quit;
    struct fh_program *prog;
    struct fh_value delta;
    struct fh_value focus;
    struct fh_value opt;
} MainLoopData;

static MainLoopData loopData;

static void quit_function(void) {
    if (fh_call_function(loopData.prog, "love_quit", NULL, 0, NULL) < 0) {
        clove_error("Error: %s\n", fh_get_error(loopData.prog));
    }
#ifdef USE_NATIVE
    game_quit();
#endif
}

static void focus_function(void) {
    loopData.focus.data.b = graphics_hasFocus();
    if (fh_call_function(loopData.prog, "love_focus", &loopData.focus, 1, NULL) == -2) {
        clove_error("Error: %s\n", fh_get_error(loopData.prog));
    }
}

static void main_clean(void) {
    joystick_close();
    ui_deinit();
    graphics_geometry_free();
    graphics_shutdown();
    filesystem_free();
    audio_close();
    fh_deinit(loopData.prog);
}

static const char ui_key_map[256] = {
    [ SDLK_LSHIFT & 0xff ] = MU_KEY_SHIFT,
    [ SDLK_RSHIFT & 0xff ] = MU_KEY_SHIFT,
    [ SDLK_LCTRL & 0xff ] = MU_KEY_CTRL,
    [ SDLK_RCTRL & 0xff ] = MU_KEY_CTRL,
    [ SDLK_LALT & 0xff ] = MU_KEY_ALT,
    [ SDLK_RALT & 0xff ] = MU_KEY_ALT,
    [ SDLK_RETURN & 0xff ] = MU_KEY_RETURN,
    [ SDLK_BACKSPACE & 0xff ] = MU_KEY_BACKSPACE,
};

static const char ui_button_map[256] = {
    [ SDL_BUTTON_LEFT & 0xff ] = MU_MOUSE_LEFT,
    [ SDL_BUTTON_RIGHT & 0xff ] = MU_MOUSE_RIGHT,
    [ SDL_BUTTON_MIDDLE & 0xff ] = MU_MOUSE_MIDDLE,
};

static struct fh_value update_args[2];

void fh_main_loop(int argc, char **argv) {
    timer_step();
    focus_function();
    matrixstack_origin();
    loopData.delta.data.num = (double) timer_getDelta();

    update_args[0] = loopData.delta;
    update_args[1] = loopData.opt;
    if (fh_call_function(loopData.prog, "love_update", update_args, 2, NULL) == -2) {
        return;
    }

#ifdef USE_NATIVE
    game_update((float) timer_getDelta());
#endif

    /*if (clove_reload) {

        clove_reload = false;
    }*/

    graphics_clear();
    if (fh_call_function(loopData.prog, "love_draw", &loopData.opt, 1, NULL) == -2) {
        return;
    }

#ifdef USE_NATIVE
    game_draw();
#endif
    ui_draw();

    graphics_swap();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT) {
            switch (event.window.event) {
                case SDL_WINDOWEVENT_ENTER:
                    graphics_setMouseFocus(true);
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    graphics_setMouseFocus(false);
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    graphics_setFocus(false);
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    graphics_setFocus(true);
                    break;
                default:
                    break;
            }
        }
        switch (event.wheel.type) {
            case SDL_MOUSEWHEEL: {
                ui_input_scroll(0, event.wheel.y * -30);
                mouse_mousewheel(event.wheel.y);
                int _what = event.wheel.y == 1 ? SDL_MOUSEBUTTONUP : SDL_MOUSEBUTTONDOWN;
                mouse_mousepressed(event.button.x, event.button.y, _what);
                mouse_setButton(event.button.button);
                break;
            }
            default:
                break;
        }
        switch (event.type) {
            case SDL_KEYDOWN: {
                int c = ui_key_map[event.key.keysym.sym & 0xff];
                if (c) {
                    ui_input_keydown(c);
                }
                keyboard_keypressed(event.key.keysym.sym);
                break;
            }
            case SDL_KEYUP: {
                int c = ui_key_map[event.key.keysym.sym & 0xff];
                if (c) {
                    ui_input_keyup(c);
                }
                keyboard_keyreleased(event.key.keysym.sym);
                break;
            }
            case SDL_TEXTINPUT: {
                const char *text = event.text.text;
                ui_input_text(text);
                keyboard_textInput(text);
                break;
            }
            case SDL_MOUSEMOTION: {
                int x = event.motion.x;
                int y = event.motion.y;
                ui_input_mouse_move(x, y);
                mouse_mousemoved(x, y);
                break;
            }
            case SDL_MOUSEBUTTONDOWN: {
                int x = event.button.x;
                int y = event.button.y;
                int btn = event.button.button;
                int ui_btn = ui_button_map[btn & 0xff];
                if (ui_btn) {
                    ui_input_mouse_down(ui_btn, x, y);
                }
                mouse_mousepressed(x, y, btn);
                mouse_setButton(btn);
                break;
            }
            case SDL_MOUSEBUTTONUP: {
                int x = event.button.x;
                int y = event.button.y;
                int btn = event.button.button;
                int ui_btn = ui_button_map[btn & 0xff];
                if (ui_btn) {
                    ui_input_mouse_up(ui_btn, x, y);
                }
                mouse_mousereleased(x, y, btn);
                mouse_setButton(0);
                break;
            }
            case SDL_JOYDEVICEADDED:
                joystick_added(event.jdevice.which);
                break;
            case SDL_JOYDEVICEREMOVED:
                joystick_remove(event.jdevice.which);
                break;
            case SDL_JOYAXISMOTION:
                break;
            case SDL_JOYBUTTONDOWN:
                joystick_buttonDown(event.jbutton.which, event.jbutton.button, event.jbutton.state);
                break;
            case SDL_JOYBUTTONUP:
                joystick_buttonUp(event.jbutton.which, event.jbutton.button, event.jbutton.state);
                break;
#ifdef CLOVE_DESKTOP
            case SDL_QUIT: {
                loopData.called_quit = true;
                quit_function();
                clove_running = false;
                break;
            }
#endif
        }
    }
    audio_updateStreams();
}

void fh_main_activity_load(int argc, char *argv[]) {
    fh_init();
    clove_reload = false;
    clove_running = true;
    loopData.called_quit = false;
    loopData.prog = fh_new_program();
    if (!loopData.prog) {
        clove_error("ERROR: out of memory for initializing language FH\n");
        return;
    }

    keyboard_init();
    joystick_init();
    timer_init();

    filesystem_init(argv[0], true);

    graphics_particlesystem_init();

    audio_init(true);
    //filesystem_setIdentity("./");

    printf("%s %s \n", "Platform:", filesystem_getOS());

    graphics_init(800, 600, 0, 1, 1);

    graphics_setBordless(0);
    graphics_setVsync(true);
    graphics_setFullscreen(false, 0);

    graphics_geometry_init();
    ui_init();

    graphics_loadAndSetIcon("icon.png");

    love_Version const *version = love_getVersion();
    printf("%s %s %d.%d.%d \n", "CLove version - ",
           version->codename, version->major, version->minor, version->revision);
    printf("FH version - %s\n", FH_VERSION);

    fh_keyboard_register(loopData.prog);
    fh_mouse_register(loopData.prog);
    fh_joystick_register(loopData.prog);
    fh_timer_register(loopData.prog);
    fh_graphics_geometry_register(loopData.prog);
    fh_image_register(loopData.prog);
    fh_graphics_register(loopData.prog);
    fh_graphics_window_register(loopData.prog);
    fh_math_register(loopData.prog);
    fh_graphics_font_register(loopData.prog);
    fh_graphics_bitmap_font_register(loopData.prog);
    fh_filesystem_register(loopData.prog);
    fh_audio_register(loopData.prog);
    fh_graphics_batch_register(loopData.prog);
    fh_event_register(loopData.prog);
    fh_graphics_mesh_register(loopData.prog);
    fh_graphics_quad_register(loopData.prog);
    fh_graphics_shader_register(loopData.prog);
    fh_graphics_particlesystem_register(loopData.prog);
    fh_ui_register(loopData.prog);
    fh_graphics_canvas_register(loopData.prog);
    fh_love_register(loopData.prog);

    bool dump_bytecode = false;
    bool run_package = false;

    if (argv[1]) {
        if (strstr(argv[1], ".love"))
            run_package = true;
        else
            clove_error("ERROR: couldn't find pack named \"%s\" to run\n", argv[1]);
    }

    if (argv[2] && strcmp(argv[2], "true") == 0) {
        dump_bytecode = true;
    }

    int ret = -1;
    if (run_package) {
        ret = fh_run_pack(loopData.prog, dump_bytecode, argv[1], "config.fh", NULL, argv, argc, false);
        if (ret == 0) {
            fh_config(loopData.prog);
        }
        ret = fh_run_pack(loopData.prog, dump_bytecode, argv[1], "main.fh", "main", argv, argc, true);
    } else {
        ret = fh_run_script_file(loopData.prog, dump_bytecode, "config.fh", NULL, argv, argc, false);
        if (ret == 0) {
            fh_config(loopData.prog);
        }
        ret = fh_run_script_file(loopData.prog, dump_bytecode, "main.fh", "main", argv, argc, true);
    }

    if (ret < 0) {
        clove_error("ERROR: %s\n", fh_get_error(loopData.prog));
        main_clean();
        return;
    }

    loopData.delta = fh_new_number(1);
    loopData.focus = fh_new_bool(false);

    loopData.opt = fh_new_map(loopData.prog);

    if (fh_call_function(loopData.prog, "love_load", NULL, 0, &loopData.opt) < 0) {
        clove_error("Error: %s\n", fh_get_error(loopData.prog));
        fh_running = false;
        main_clean();
        return;
    }


#ifdef USE_NATIVE
    game_load();
#endif

#ifdef CLOVE_WEB
    emscripten_set_main_loop(lua_main_loop, 60, 1);
#else
    while (clove_running && fh_running) {
        fh_main_loop(argc, argv);
    }
#endif

    /*
     * The logic:
     * When you set an error in FH the boolean "fh_running" will be set automatically to
     * 'false' meaning CLove will stop from running. If that's the case then we want to
     * print the error made because of FH!
     *
     * NOTE:
     * When the error happened because of CLove (not FH) then fh_running will be still set to
     * its default value, 'true', and the "if" from below won't be called but we will still
     * get the errors because of 'clove_error' function called in the errornous function.
     */
    if (!fh_running) {
        clove_error("ERROR: %s\n", fh_get_error(loopData.prog));
    }

    if (!loopData.called_quit) {
        quit_function();
    }
    main_clean();
}

#endif
