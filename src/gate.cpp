#include "../headers/gate.h"

std::string gate_to_string(gate g) {
  return "{starting_state: " + std::to_string(g.starting_state) + 
        ", t1: " + std::to_string(g.t1) + 
        ", t2: " + std::to_string(g.t2) +
        "}";
}

bool particle_passes_gate(particle p, gate g, float length) {
  float t = next_lap_elapsed(p,length) + p.wait;
  float m = mod(t,g.t1+g.t2);
  bool b = (0 <= m && m < g.t1);
  return g.starting_state ? !b : b;
}

void print(float velocity, float initial_wait, std::function<std::vector<float>(float,float)> simulate_fn) {
  std::vector<float> survival_rates = simulate_fn(velocity,initial_wait);
  std::cout << "v=" << std::to_string(velocity) << ":   " 
            << "initial_wait: " << std::to_string(initial_wait) <<"   "
            << "expected_resets: " << std::to_string(expected_resets(survival_rates)) << ":   " 
            << "distribution: [" <<  stringify_vals(survival_rates) << "]"
            << std::endl;
}