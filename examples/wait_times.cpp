#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"
#include "../headers/reset.h"
#include "../headers/gate.h"

float wait_time(particle p, gate g, float length) {
  float dt;
  if (mod(p.lifespan,g.t1+g.t2) <= g.t2) {
    dt = p.lifespan - ((2*length) / p.velocity);
  } else {
    dt = g.t1 + (int)(p.lifespan / (g.t1+g.t2)) * (g.t1+g.t2) - ((2*length) / p.velocity);
  }
  return dt - mod(p.elapsed_time,g.t1+g.t2);
}

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000000;

  gate g = {.starting_state=0,.t1=1.f,.t2=1.f};

  auto should_reset_fn = [&](particle p){
    return particle_does_lap(p,length) && particle_passes_gate(p,g,length);
  };

  auto wait_time_fn = [&](particle p) {return wait_time(p,g,length);};

  auto reset_particle = [&] (simulation* sim, particle p) {
    particle p1 = sim->create_particle();
    p1.elapsed_time = next_lap_elapsed(p,length);
    p1.wait = wait_time_fn(p1);
    return p1;
  };

  auto simulate_fn = [&](float velocity) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(wait_time_fn);
    return survival_rates(&sim,reset_config(should_reset_fn,reset_particle));
  };

  auto print_fn = [&](float velocity) {
    std::vector<float> survival_rates = simulate_fn(velocity);
    std::cout << "v=" << std::to_string(velocity) << ":   " 
              << "expected_resets: " << std::to_string(expected_resets(survival_rates)) << ":   " 
              << "distribution: [" <<  stringify_vals(survival_rates) << "]"
              << std::endl;
  };

  std::cout << "Resets with mean lifespan " << mean_lifespan << ", gate " << gate_to_string(g) << ", and velocity v:" << std::endl;
  print_fn(1.f);
}