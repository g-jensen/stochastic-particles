#pragma once

#include <random>

std::uniform_real_distribution<> dis(0.0, 1.0);
std::random_device rd;
std::mt19937 gen(rd());

float random_probability() {
  return dis(gen);
}