#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/particle.h"

uint surivial_count(simulation& sim, float length) {
  uint count = 0;
  for (particle& p : sim.particles) {
    if (particle_does_lap(p,length)) {
      count++;
    }
  }
  return count;
}

float survival_rate(simulation& sim, float length) {
  return (float)surivial_count(sim,length) / sim.particles.size();
}

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000000;

  auto simulate_fn = [&](float velocity) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init();
    return survival_rate(sim,length);
  };

  auto print_fn = [&](float velocity) {
    std::cout << "v=" << std::to_string(velocity) << ":   {simulated_value: " << std::to_string(simulate_fn(velocity)) << ", actual_value: " << std::to_string(exp((2*length) / - (velocity* mean_lifespan))) << "}" << std::endl;
  };

  std::cout << "Survival rates with mean lifespan " << mean_lifespan << " and velocity v:" << std::endl;
  print_fn(0.f);
  print_fn(0.25f);
  print_fn(0.5f);
  print_fn(1.f);
  print_fn(2.f);
}