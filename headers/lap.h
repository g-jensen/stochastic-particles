#pragma once

#include <functional>
#include <iostream>
#include "distribution.h"
#include "simulation.h"
#include "io.h"

particle lap_particle(simulation* sim, particle p, float length);
particle killed_particle(simulation* sim, particle p);

struct lap_config {
  std::function<bool(particle)> should_lap_fn;
  std::function<particle(simulation*,particle)> lap_particle_fn;
  std::function<particle(simulation*,particle)> killed_particle_fn;

  lap_config(
    std::function<bool(particle)> should_lap_fn, 
    std::function<particle(simulation*,particle)> lap_particle_fn);
  lap_config(
    std::function<bool(particle)> should_lap_fn, 
    std::function<particle(simulation*,particle)> lap_particle_fn,
    std::function<particle(simulation*,particle)> killed_particle_fn);
};

uint simulate_lap(simulation* sim, lap_config cfg);

std::vector<float> survival_rates(simulation* sim, lap_config cfg);

float expected_laps(std::vector<float> lap_probabilities);

std::vector<float> simulate(
  float velocity,
  float initial_wait,
  uint particle_count,
  std::function<float(float)> death_distribution_fn,
  lap_config lap_config);
