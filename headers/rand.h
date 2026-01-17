#pragma once

#include <random>
#include <functional>

void seed_random(int* seed);
float random_probability();
float average(std::function<float(void)> f, uint n);