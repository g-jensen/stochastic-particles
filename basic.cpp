#include <iostream>
#include <cmath>
#include "simulation.h"

// Inverse of f(t) = 1 - e^{-t/mean}.
float exponential_distribution(float rand, float mean) {
  return -mean * log(1-rand);
}

int main() {
  float mean = 1.f;
  auto death_distribution_fn = [mean](float rand) {return exponential_distribution(rand,mean);};
  int particle_count = 1000;

  simulation sim(death_distribution_fn,particle_count);
  std::cout << sim.averge_lifespan() << std::endl;
}