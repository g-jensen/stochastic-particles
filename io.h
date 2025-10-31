#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "rand.h"

std::string stringify_floats(std::vector<float> v) {
  std::string s = std::to_string(v[0]);
  for (int i = 1; i < v.size(); i++) {
    s += ", " + std::to_string(v[i]);
  }
  return s;
}

void print_simulated_average(std::function<std::function<float(void)>(float)> simulate_fn, float velocity) {
  std::cout << "v=" << std::to_string(velocity) << ":   " << average(simulate_fn(velocity),1000) << std::endl;
}