#pragma once

#include <random>
#include <functional>

std::uniform_real_distribution<> dis(0.0, 1.0);
std::random_device rd;
std::mt19937 gen(rd());

float random_probability() {
  return dis(gen);
}

float average(std::function<float(void)> f, uint n) {
  float total = 0.f;
  for (uint i = 0; i < n; i++) {
    total += f();
  }
  return total / n;
}