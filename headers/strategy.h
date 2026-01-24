#pragma once

#include "particle.h"
#include "gate.h"
#include "math.h"
#include "simulation.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

typedef std::function<float(particle, gate, float)> wait_strategy;

struct value_result {
  float omega;
  float expected_laps;
  std::vector<float> distribution;
};

bool is_lifespan_during_gate_on(float lifespan, gate g);
float no_wait_time(particle p, gate g, float length);
float late_wait_time(particle p, gate g, float length);
float early_wait_time(particle p, gate g, float length);
particle reset_particle_with_wait(simulation* sim, particle p, float length,
                                   std::function<float(particle)> wait_time_fn);
value_result estimate_value(float omega, gate g, float velocity, float mean_lifespan,
                            int particle_count, float length, wait_strategy strategy);
void run_strategy_simulation(int argc, char* argv[], wait_strategy strategy, 
                             const std::string& strategy_name);
