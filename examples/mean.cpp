#include <iostream>
#include "../distribution.h"
#include "../simulation.h"

float averge_lifespan(simulation& sim) {
  float lifespan_sum = 0;
  for (particle& p : sim.particles) {
    lifespan_sum += p.lifespan;
  }
  return lifespan_sum / sim.particles.size();
}

int main() {
  float mean = 1.f;
  auto death_distribution_fn = [mean](float rand) {return exponential_distribution(rand,mean);};
  int particle_count = 1000;

  simulation sim(death_distribution_fn,particle_count,1.f);
  std::cout << averge_lifespan(sim) << std::endl;
}