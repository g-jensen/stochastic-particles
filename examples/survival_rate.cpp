#include <iostream>
#include "../distribution.h"
#include "../simulation.h"
#include "../particle.h"

uint surivial_count(simulation& sim, float length) {
  uint count = 0;
  for (particle& p : sim.particles) {
    if (particle_surives(p,length)) {
      count++;
    }
  }
  return count;
}

float survival_rate(simulation& sim, float length) {
  return (float)surivial_count(sim,length) / sim.particles.size();
}

int main() {
  float mean_lifespan = 1.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000;

  auto simulate_fn = [&](float velocity) {
    return [&, velocity]() {
      simulation sim(death_distribution_fn,particle_count,velocity);
      sim.init();
      return survival_rate(sim,length);
    };
  };

  auto print_fn = [&](float velocity) {
    std::cout << "v=" << std::to_string(velocity) << ":   " << average(simulate_fn(velocity),1000) << std::endl;
  };
 
  std::cout << "Survival Rates with Velocity v:" << std::endl;
  print_fn(0.f);
  print_fn(0.25f);
  print_fn(0.5f);
  print_fn(1.f);
  print_fn(2.f);
}