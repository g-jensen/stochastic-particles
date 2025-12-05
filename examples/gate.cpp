#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"
#include "../headers/reset.h"

// gate that is periodically starting_state for t1 seconds and then !starting_state for t2 seconds.
struct gate {
  bool starting_state;
  float t1;
  float t2;
};

std::string gate_to_string(gate g) {
  return "{starting_state: " + std::to_string(g.starting_state) + 
        ", t1: " + std::to_string(g.t1) + 
        ", t2: " + std::to_string(g.t2) +
        "}";
}

float mod(float a, float b) {
  return a - b * (int)((int)a / (int)b);
}

bool particle_passes_gate(particle p, gate g, float length) {
  float t = (length / p.velocity) + p.initial_wait; // time that it takes for the particle to go `length`
  float m = mod(t,g.t1+g.t2);
  bool b = (0 <= m && m < g.t1);
  return g.starting_state ? !b : b;
}

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000000;

  gate g = {.starting_state=1,.t1=1.f,.t2=1.f};

  auto should_reset_fn = [&](particle p){
    return particle_does_lap(p,length) && particle_passes_gate(p,g,length);
  };

  auto simulate_fn = [&](float velocity, float initial_wait) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(initial_wait);
    return survival_rates(sim,should_reset_fn);
  };

  auto print_fn = [&](float velocity, float initial_wait) {
    std::vector<float> survival_rates = simulate_fn(velocity,initial_wait);
    std::cout << "v=" << std::to_string(velocity) << ":   " 
              << "initial_wait: " << std::to_string(initial_wait) <<"   "
              << "distribution: [" <<  stringify_vals(survival_rates) << "]"
              << std::endl;
  };

  std::cout << "Resets with mean lifespan " << mean_lifespan << ", gate " << gate_to_string(g) << ", and velocity v:" << std::endl;
  for (float wait = 0.f; wait <= 15.f; wait+=0.1f) {
    print_fn(1.f,wait);
  }
}