/*
#   clove
#
#   Copyright (C) 2017-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "utils.h"

#ifdef CLOVE_DESKTOP
#include "../3rdparty/glew/include/GL/glew.h"
#endif

#ifdef CLOVE_WEB
#include <GL/glew.h>
#endif

#ifdef CLOVE_ANDROID
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
