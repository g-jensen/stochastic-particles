#pragma once

#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include <functional>

uint simulate_reset(simulation& sim, std::function<bool(particle)> should_reset_fn);

std::vector<float> survival_rates(simulation& sim, std::function<bool(particle)> should_reset_fn);