/*
#   clove
#
#   Copyright (C) 2019 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#pragma once

#include "../3rdparty/FH/src/fh.h"
#include "../3rdparty/FH/src/value.h"

#include "../include/utils.h"

char const *fh_tools_toStringOrError(struct fh_program *prog, struct fh_value *args, int index);
double fh_tools_toNumberOrError(struct fh_program *prog, struct fh_value *args, int index);
