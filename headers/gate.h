#pragma once
#include <string>
#include <functional>
#include <iostream>
#include "io.h"
#include "particle.h"
#include "math.h"
#include "simulation.h"
#include "lap.h"

// gate that is periodically starting_state for t1 seconds and then !starting_state for t2 seconds.
struct gate {
  bool starting_state;
  float t1;
  float t2;
};

std::string gate_to_string(gate g);
bool particle_passes_gate(particle p, gate g, float length);