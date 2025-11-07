#pragma once

#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "rand.h"

template<typename T>
inline std::string stringify_vals(std::vector<T> v) {
  std::string s = std::to_string(v[0]);
  for (int i = 1; i < v.size(); i++) {
    s += ", " + std::to_string(v[i]);
  }
  return s;
}