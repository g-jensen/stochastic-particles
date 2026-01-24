#include "../headers/strategy.h"
#include "../headers/reset.h"
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/cli.h"
#include "../headers/rand.h"
#include "../headers/io.h"
#include <vector>
#include <iostream>

bool is_lifespan_during_gate_on(float lifespan, gate g) {
  float m = mod(lifespan, g.t1 + g.t2);
  bool b = (0 < m && m <= g.t1);
  return g.starting_state ? b : !b;
}

float no_wait_time(particle p, gate g, float length) {
  return 0.f;
}

float late_wait_time(particle p, gate g, float length) {
  float tau = (2 * length) / p.velocity;
  float period = g.t1 + g.t2;
  float dt;
  if (is_lifespan_during_gate_on(p.lifespan, g)) {
    dt = p.lifespan - tau;
  } else {
    float gate_offset = g.starting_state ? g.t1 : 0;
    dt = gate_offset + (floor(p.lifespan / period) * period) - tau;
  }
  float offset = mod(p.elapsed_time, period);
  return std::max(0.f, dt - offset);
}

float early_wait_time(particle p, gate g, float length) {
  float tau = (2 * length) / p.velocity;
  float period = g.t1 + g.t2;
  float offset = mod(p.elapsed_time, period);
  float arrival_if_no_wait = offset + tau;
  float arrival_mod = mod(arrival_if_no_wait, period);
  bool lands_in_on = (0 < arrival_mod && arrival_mod <= g.t1);
  if (g.starting_state ? lands_in_on : !lands_in_on) {
    return 0.f;
  }
  float time_until_on;
  if (g.starting_state) {
    time_until_on = period - arrival_mod;
  } else {
    if (arrival_mod <= g.t1) {
      time_until_on = g.t1 - arrival_mod;
    } else {
      time_until_on = period + g.t1 - arrival_mod;
    }
  }
  float min_wait = time_until_on + 0.0001f;
  if (min_wait + tau > p.lifespan) {
    return late_wait_time(p, g, length);
  }
  return min_wait;
}

particle reset_particle_with_wait(simulation* sim, particle p, float length,
                                   std::function<float(particle)> wait_time_fn) {
  particle p1 = reset_particle(sim, p, length);
  p1.wait = wait_time_fn(p1);
  return p1;
}

value_result estimate_value(float omega, gate g, float velocity, float mean_lifespan,
                            int particle_count, float length, wait_strategy strategy) {
  auto death_distribution_fn = [&](float rand) {
    return exponential_distribution(rand, mean_lifespan);
  };

  auto should_reset_fn = [&](particle p) {
    return particle_does_lap(p, length) && particle_passes_gate(p, g, length);
  };

  auto wait_time_fn = [&](particle p) { return strategy(p, g, length); };

  auto reset_particle_fn = [&](simulation* sim, particle p) {
    return reset_particle_with_wait(sim, p, length, wait_time_fn);
  };

  simulation sim(death_distribution_fn, particle_count, velocity);

  for (int i = 0; i < particle_count; i++) {
    particle p = sim.create_particle();
    p.elapsed_time = omega;
    p.wait = strategy(p, g, length);
    sim.particles.push_back(p);
  }

  std::vector<float> rates = survival_rates(&sim, reset_config(should_reset_fn, reset_particle_fn));

  return {omega, expected_resets(rates), rates};
}

void run_strategy_simulation(int argc, char* argv[], wait_strategy strategy,
                             const std::string& strategy_name) {
  int seed = arg_int(argc, argv, "-s", -1);
  seed_random(&seed);

  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  float t1 = arg_float(argc, argv, "-t1", 1.f);
  float t2 = arg_float(argc, argv, "-t2", 1.f);
  bool starting_state = arg_int(argc, argv, "-gs", 0) != 0;
  float omega = arg_float(argc, argv, "-offset", 0.f);
  int particle_count = arg_int(argc, argv, "-n", 100000);

  float length = 1.f;
  gate g = {.starting_state = starting_state, .t1 = t1, .t2 = t2};

  value_result result = estimate_value(omega, g, velocity, mean_lifespan,
                                       particle_count, length, strategy);

  std::cout << "{\n"
            << "  \"strategy\": \"" << strategy_name << "\",\n"
            << "  \"velocity\": " << velocity << ",\n"
            << "  \"tau\": " << (2 * length / velocity) << ",\n"
            << "  \"mean_lifespan\": " << mean_lifespan << ",\n"
            << "  \"lambda\": " << (1.0 / mean_lifespan) << ",\n"
            << "  \"gate_t1\": " << t1 << ",\n"
            << "  \"gate_t2\": " << t2 << ",\n"
            << "  \"particle_count\": " << particle_count << ",\n"
            << "  \"offset\": " << omega << ",\n"
            << "  \"expected_laps\": " << result.expected_laps << ",\n"
            << "  \"distribution\": " << json_array(result.distribution) << ",\n"
            << "  \"seed\": " << seed << "\n"
            << "}" << std::endl;
}
