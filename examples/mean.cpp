#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"

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
  sim.init();
  std::cout << "{simulated_mean: " << averge_lifespan(sim) << ", actual_mean: " << mean << "}" << std::endl;
}