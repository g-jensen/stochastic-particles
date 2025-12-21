#include "../headers/gate.h"

std::string gate_to_string(gate g) {
  return "{starting_state: " + std::to_string(g.starting_state) + 
        ", t1: " + std::to_string(g.t1) + 
        ", t2: " + std::to_string(g.t2) +
        "}";
}

bool particle_passes_gate(particle p, gate g, float length) {
  float t = (length / p.velocity) + p.initial_wait; // time that it takes for the particle to go `length`
  float m = mod(t,g.t1+g.t2);
  bool b = (0 <= m && m < g.t1);
  return g.starting_state ? !b : b;
}