#pragma once

#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include <functional>

particle reset_particle(simulation* sim, particle p, float length);
particle killed_particle(simulation* sim, particle p);

struct reset_config {
  std::function<bool(particle)> should_reset_fn;
  std::function<particle(simulation*,particle)> reset_particle_fn;
  std::function<particle(simulation*,particle)> killed_particle_fn;

  reset_config(
    std::function<bool(particle)> should_reset_fn, 
    std::function<particle(simulation*,particle)> reset_particle_fn);
  reset_config(
    std::function<bool(particle)> should_reset_fn, 
    std::function<particle(simulation*,particle)> reset_particle_fn,
    std::function<particle(simulation*,particle)> killed_particle_fn);
};

uint simulate_reset(simulation* sim, reset_config cfg);

std::vector<float> survival_rates(simulation* sim, reset_config cfg);

float expected_resets(std::vector<float> reset_probabilities);

std::vector<float> simulate(
  float velocity,
  float initial_wait,
  uint particle_count,
  std::function<float(float)> death_distribution_fn,
  reset_config reset_config);