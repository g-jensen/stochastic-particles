#include <iostream>
#include <algorithm>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"
#include "../headers/reset.h"
#include "../headers/gate.h"
#include "../headers/cli.h"
#include "../headers/rand.h"

bool is_lifespan_during_gate_on(particle p, gate g) {
  float m = mod(p.lifespan,g.t1+g.t2);
  bool b = (0 < m && m <= g.t1);
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

int main(int argc, char* argv[]) {
  int seed = arg_int(argc, argv, "-s", -1);
  seed_random(&seed);
  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  float t1 = arg_float(argc, argv, "-t1", 1.f);
  float t2 = arg_float(argc, argv, "-t2", 1.f);
  bool starting_state = arg_int(argc, argv, "-gs", 0) != 0;
  float length = 1.f;
  int particle_count = 1000000;
  gate g = {.starting_state=starting_state,.t1=t1,.t2=t2};

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};

  auto should_reset_fn = [&](particle p){
    return particle_does_lap(p,length) && particle_passes_gate(p,g,length);
  };

  auto wait_time_fn = [&](particle p) {return wait_time(p,g,length);};

  auto reset_particle_fn = [&] (simulation* sim, particle p) {
    return reset_particle(sim,p,length,wait_time_fn);
  };

  simulation sim(death_distribution_fn,particle_count,velocity);
  sim.init(wait_time_fn);
  std::vector<float> rates = survival_rates(&sim,reset_config(should_reset_fn,reset_particle_fn));

  std::cout << "{\n"
            << "  \"velocity\": " << velocity << ",\n"
            << "  \"mean_lifespan\": " << mean_lifespan << ",\n"
            << "  \"gate_starting_state\": " << (starting_state ? "true" : "false") << ",\n"
            << "  \"gate_t1\": " << t1 << ",\n"
            << "  \"gate_t2\": " << t2 << ",\n"
            << "  \"expected_resets\": " << expected_resets(rates) << ",\n"
            << "  \"distribution\": " << json_array(rates) << ",\n"
            << "  \"seed\": " << seed << "\n"
            << "}" << std::endl;
}
