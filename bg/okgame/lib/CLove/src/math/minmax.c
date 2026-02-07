/*
#   clove
#
#   Copyright (C) 2016-2020 Muresan Vlad
#
#   This project is free software; you can redistribute it and/or modify it
#   under the terms of the MIT license. See LICENSE.md for details.
*/
#include "../include/minmax.h"

int max(int i, int j) {
  return i > j ? i : j;
}

int min(int i, int j) {
  return i < j ? i : j;
}

int clamp(int a, int i, int k) {
  return max(i, min(k, a));
}

float maxf(float i, float j) {
  return i > j ? i : j;
}

float minf(float i, float j) {
  return i < j ? i : j;
}

float clampf(float a, float i, float k) {
  return maxf(i, minf(k, a));
}

