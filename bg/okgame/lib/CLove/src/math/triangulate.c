/*
#   clove
#
#   Copyright (C) 2021 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/

#include "../include/triangulate.h"

static float crossVerts(float const* verts, int i, int j, int k) {
  float dx1 = verts[j*2]   - verts[i*2];
  float dy1 = verts[j*2+1] - verts[i*2+1];
  float dx2 = verts[k*2]   - verts[j*2];
  float dy2 = verts[k*2+1] - verts[j*2+1];
  return dx1 * dy2 - dy1 * dx2;
}

bool math_isConvex(float const* verts, int count) {
  int i = count - 2;
  int j = count - 1;
  int k = 0;

  float w = crossVerts(verts, i, j, k);

  while(k+1 < count) {
    i = j;
    j = k;
    ++k;

    float w2 = crossVerts(verts, i, j, k);

    if((int)w*w2 < 0.0f) {
      return false;
    }
  }

  return true;
}
