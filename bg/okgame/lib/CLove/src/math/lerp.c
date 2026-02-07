#include "../include/lerp.h"

float lerp(float a, float b, float t) {
  return a + (b-a) * t;
}
