#pragma once

#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include <functional>

particle reset_particle(simulation* sim, particle p);
particle killed_particle(simulation* sim, particle p);

struct reset_config {
  std::function<bool(particle)> should_reset_fn;
  std::function<particle(simulation*,particle)> reset_particle_fn;
  std::function<particle(simulation*,particle)> killed_particle_fn;

  reset_config(std::function<bool(particle)> should_reset_fn) {
    this->should_reset_fn=should_reset_fn;
    this->reset_particle_fn=reset_particle;
    this->killed_particle_fn=killed_particle;
  }
};

uint simulate_reset(simulation* sim, reset_config cfg);

std::vector<float> survival_rates(simulation* sim, reset_config cfg);