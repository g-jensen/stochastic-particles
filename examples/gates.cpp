#include "../headers/gate.h"

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  int particle_count = 1000000;
  gate g = {.starting_state=0,.t1=1.f,.t2=1.f};

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  
  auto should_reset_fn = [&](particle p){
    return particle_does_lap(p,length) && particle_passes_gate(p,g,length);
  };

  auto reset_particle_fn = [&] (simulation* sim, particle p) {return reset_particle(sim,p,length);};

  auto simulate_fn = [&](float velocity, float initial_wait) {
    return simulate(velocity,initial_wait,particle_count,death_distribution_fn,reset_config(should_reset_fn,reset_particle_fn));
  };

  auto print_fn = [&](float velocity, float initial_wait) {
    print(velocity,initial_wait,simulate_fn);
  };

  std::cout << "Resets with mean lifespan " << mean_lifespan << ", gate " << gate_to_string(g) << ", and velocity v:" << std::endl;
  for (float wait = 0.f; wait <= 15.f; wait+=0.1f) {
    print_fn(1.f,wait);
  }
}