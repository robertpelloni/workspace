/*
#   clove
#
#   Copyright (C) 2019-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#ifndef __clove_thread_
#define __clove_thread_

#include "../3rdparty/SDL2/include/SDL.h"

SDL_Thread* createThread(int (SDLCALL * fn) (void *), const char* name, void *data);



#endif
