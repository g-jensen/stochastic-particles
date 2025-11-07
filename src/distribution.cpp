#include "../headers/distribution.h"

float exponential_distribution(float rand, float mean) {
  assert(0 <= rand && rand <= 1);
  return -mean * log(1-rand);
}