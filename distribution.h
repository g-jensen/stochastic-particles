#pragma once

#include <cmath>
#include <cassert>

// Inverse of f(t) = 1 - e^{-t/mean}. Note: f'(t)=1/mean * e^{-t/mean} which is what is meant by exponential.
float exponential_distribution(float rand, float mean) {
  assert(0 <= rand && rand <= 1);
  return -mean * log(1-rand);
}