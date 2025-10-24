#pragma once

#include <cmath>

// Inverse of f(t) = 1 - e^{-t/mean}. Note: f'(t)=1/mean * e^{-t/mean} which is what is meant by exponential.
float exponential_distribution(float rand, float mean) {
  return -mean * log(1-rand);
}