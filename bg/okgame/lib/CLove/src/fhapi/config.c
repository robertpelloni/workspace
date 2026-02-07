/*
#   clove
#
#   Copyright (C) 2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "config.h"

#include "../3rdparty/FH/src/value.h"

#include "../include/love.h"
#include "../include/graphics.h"
#include "../include/filesystem.h"

int fh_config(struct fh_program *prog) {

    struct fh_value config = fh_new_map(prog);

    if (fh_call_function(prog, "love_config", &config, 1, NULL) < 0) {
        return fh_set_error(prog, "ERROR in love_config: %s\n", fh_get_error(prog));
    }

    struct fh_map* map = GET_VAL_MAP(&config);

    struct fh_value ret, key;

    key = fh_new_string(prog, "window_title");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setTitle(GET_VAL_STRING_DATA(&ret));
    }

    key = fh_new_string(prog, "window_width");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setWindowSize(fh_get_number(&ret), graphics_getHeight());
    }

    key = fh_new_string(prog, "window_height");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setWindowSize(graphics_getWidth(), fh_get_number(&ret));
    }

    key = fh_new_string(prog, "window_min_width");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setMinSize(fh_get_number(&ret), graphics_getHeight());
    }

    key = fh_new_string(prog, "window_min_height");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setMinSize(graphics_getWidth(), fh_get_number(&ret));
    }

    key = fh_new_string(prog, "window_max_width");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setMaxSize(fh_get_number(&ret), graphics_getHeight());
    }

    key = fh_new_string(prog, "window_max_height");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setMaxSize(graphics_getWidth(), fh_get_number(&ret));
    }

    key = fh_new_string(prog, "window_x");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setPosition(fh_get_number(&ret), graphics_getWindowY());
    }

    key = fh_new_string(prog, "window_y");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setPosition(graphics_getWindowX(), fh_get_number(&ret));
    }

    key = fh_new_string(prog, "window_bordless");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setBordless(fh_get_bool(&ret));
    }

    key = fh_new_string(prog, "window_resizable");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setWindowResizable(fh_get_bool(&ret));
    }

    key = fh_new_string(prog, "window_vsync");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setVsync(fh_get_bool(&ret));
    }

    key = fh_new_string(prog, "window_destroy");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        if (fh_get_bool(&ret)) {
            graphics_shutdown();
        }
    }

    key = fh_new_string(prog, "window_icon");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_loadAndSetIcon(GET_VAL_STRING_DATA(&ret));
    }

    key = fh_new_string(prog, "window_fullscreen");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        bool fullscreen = fh_get_bool(&ret);
        graphics_setFullscreen(fullscreen, fullscreen ? "fullscreen" : NULL);
    }

    key = fh_new_string(prog, "window_fullscreentype");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        graphics_setFullscreen(true, GET_VAL_STRING_DATA(&ret));
    }

    key = fh_new_string(prog, "version");
    if (fh_get_map_object_value(map, &key, &ret) == 0) {
        const char* target_version = GET_VAL_STRING_DATA(&ret);
        const char* current_version = love_getVersion()->strVersion;
        if (strcmp(target_version, current_version) != 0) {
            clove_error("Warning: Target version from config file %s is different than current running clove version %s", target_version, current_version);
        }
    }

    return 0;
}
