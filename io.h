#pragma once

#include <string>
#include <vector>

std::string stringify_floats(std::vector<float> v) {
  std::string s = std::to_string(v[0]);
  for (int i = 1; i < v.size(); i++) {
    s += ", " + std::to_string(v[i]);
  }
  return s;
}