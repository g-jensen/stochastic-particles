#include <iostream>
#include "distribution.h"
#include "simulation.h"

int main() {
  float mean = 1.f;
  auto death_distribution_fn = [mean](float rand) {return exponential_distribution(rand,mean);};
  int particle_count = 1000;

  simulation sim(death_distribution_fn,particle_count);
  std::cout << sim.averge_lifespan() << std::endl;
}