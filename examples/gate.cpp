#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"

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
  return a - b * ((int)a / (int)b);
}

bool particle_passes_gate(particle p, gate g, float length) {
  float t = (length / p.velocity) + p.initial_wait; // time that it takes for the particle to go `length`
  float m = mod(t,g.t1+g.t2);
  bool b = (0 <= m && m < g.t1);
  return g.starting_state ? !b : b;
}

uint simulate_reset(simulation& sim, float length, gate g) {
  uint count = 0;
  for (particle& p : sim.particles) {
    if (particle_travels_length(p,length) && particle_passes_gate(p,g,length)) {
      p=sim.create_particle();
      count++;
    } else {
      p.state=particle_state::DEAD;
    }
  }
  return count;
}

std::vector<float> survival_rates(simulation& sim, float length, gate g) {
  std::vector<float> survival_rates;
  const uint particle_count = sim.particles.size();
  uint prev_survival_count;
  uint survival_count = particle_count;
  do {
    prev_survival_count = survival_count;
    survival_count = simulate_reset(sim,length,g);
    survival_rates.push_back((float)(prev_survival_count - survival_count) / particle_count);
  } while (survival_count > 0);
  return survival_rates;
}

int main() {
  float mean_lifespan = 1.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000000;

  gate g = {.starting_state=0,.t1=1.f,.t2=1.f};

  auto simulate_fn = [&](float velocity, float initial_wait) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(initial_wait);
    return survival_rates(sim,length,g);
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
  // print_fn(0.f);
  // print_fn(0.25f);
  // print_fn(0.5f);
  // print_fn(0.75f);
  // print_fn(1.f);
  // print_fn(1.25f);
  // print_fn(1.50f);
  // print_fn(1.75f);
  // print_fn(2.f);
}