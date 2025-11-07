#pragma once

#include <random>
#include <functional>

float random_probability();

float average(std::function<float(void)> f, uint n);