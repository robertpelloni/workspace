/*
#   clove
#
#   Copyright (C) 2015-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#ifdef EMSCRIPTEN
# include <emscripten.h>
#endif

#ifdef USE_LUA
#include "include/lua_mainactivity.h"
#endif
#ifdef USE_FH
#include "include/fh_mainactivity.h"
#endif

int main(int argc, char* argv[]) {
  #ifdef USE_LUA
    lua_main_activity_load(argc, argv);
  #endif
  #ifdef USE_FH
    fh_main_activity_load(argc, argv);
  #endif
  return 0;
}
