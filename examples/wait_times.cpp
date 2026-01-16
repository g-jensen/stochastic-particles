#include <iostream>
#include <algorithm>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"
#include "../headers/reset.h"
#include "../headers/gate.h"

bool is_lifespan_during_gate_on(particle p, gate g) {
  bool b = mod(p.lifespan,g.t1+g.t2) <= g.t2;
  return g.starting_state ? b : !b;
}

float gate_offset(gate g) {
  return g.starting_state ? g.t1 : 0;
}

float wait_time(particle p, gate g, float length) {
  float dt;
  if (is_lifespan_during_gate_on(p,g)) {
    dt = p.lifespan - ((2*length) / p.velocity);
  } else {
    dt = gate_offset(g) + (floor(p.lifespan / (g.t1+g.t2)) * (g.t1+g.t2)) - ((2*length) / p.velocity);
  }
  return std::max(0.f,dt - mod(p.elapsed_time,g.t1+g.t2));
}

particle reset_particle(simulation* sim, particle p, float length, std::function<float(particle)> wait_time_fn) {
  particle p1 = reset_particle(sim,p,length);
  p1.wait = wait_time_fn(p1);
  return p1;
}

std::vector<float> simulate(
  float velocity,
  std::function<float(particle)> wait_time_fn,
  uint particle_count,
  std::function<float(float)> death_distribution_fn,
  reset_config reset_config) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(wait_time_fn);
    return survival_rates(&sim,reset_config);
}

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  int particle_count = 1000000;
  gate g = {.starting_state=0,.t1=1.f,.t2=1.f};

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};

  auto should_reset_fn = [&](particle p){
    return particle_does_lap(p,length) && particle_passes_gate(p,g,length);
  };

  auto wait_time_fn = [&](particle p) {return wait_time(p,g,length);};

  auto reset_particle_fn = [&] (simulation* sim, particle p) {
    return reset_particle(sim,p,length,wait_time_fn);
  };

  auto simulate_fn = [&](float velocity) {
    return simulate(velocity,wait_time_fn,particle_count,death_distribution_fn,reset_config(should_reset_fn,reset_particle_fn));
  };

  auto print_fn = [&](float velocity) {print(velocity,simulate_fn);};

  std::cout << "Resets with mean lifespan " << mean_lifespan << ", gate " << gate_to_string(g) << ", and velocity v:" << std::endl;
  print_fn(1.f);
}