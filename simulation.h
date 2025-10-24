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
  // assumes 0 <= input <= 1 and 0 <= output <= inf
  std::function<float(float)> death_distribution_fn;
  std::vector<particle> particles;
  
  simulation(std::function<float(float)> death_distribution_fn, uint particle_count, float velocity) {
    this->death_distribution_fn = death_distribution_fn;
    for (uint i = 0; i < particle_count; i++) {
      particle p = {.velocity=velocity, .lifespan=death_distribution_fn(random_probability())};
      particles.push_back(p);
    }
  }

  float averge_lifespan() {
    float lifespan_sum = 0;
    for (particle& p : particles) {
      lifespan_sum += p.lifespan;
    }
    return lifespan_sum / particles.size();
  }
};