#pragma once

#include "rand.h"
#include <functional>
#include <vector>

struct particle {
  float velocity;
  float lifespan;
};

class simulation {
public:
  std::vector<particle> particles;
  
  simulation(std::function<float(float)> death_distribution_fn, uint particle_count, float velocity) {
    this->death_distribution_fn = death_distribution_fn;
    this->particle_count = particle_count;
    this->velocity = velocity;
  }

  void init() {
    for (uint i = 0; i < particle_count; i++) {
      particles.push_back(create_particle());
    }
  }

  particle create_particle() {
    return {.velocity=velocity, .lifespan=death_distribution_fn(random_probability())};
  }

private:
  // assumes 0 <= input <= 1 and 0 <= output <= inf
  std::function<float(float)> death_distribution_fn;
  float velocity;
  uint particle_count;
};