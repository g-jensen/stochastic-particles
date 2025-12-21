#include "../headers/math.h"

float mod(float a, float b) {
  return a - b * (int)((int)a / (int)b);
}