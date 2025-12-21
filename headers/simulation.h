#pragma once

#include <functional>
#include <vector>
#include "rand.h"
#include "particle.h"

class simulation {
public:
  std::vector<particle> particles;
  
  simulation(std::function<float(float)> death_distribution_fn, uint particle_count, float velocity);

  void init();
  void init(float initial_wait);
  void init(std::function<float(particle)> initial_wait_fn);
  particle create_particle();
  particle create_particle(float initial_wait);
  particle create_particle(std::function<float(particle)> initial_wait_fn);

private:
  // assumes 0 <= input <= 1 and 0 <= output <= inf
  std::function<float(float)> death_distribution_fn;
  float velocity;
  uint particle_count;
};