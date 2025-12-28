#include "../headers/reset.h"

particle reset_particle(simulation* sim, particle p, float length) {
  particle p1 = sim->create_particle();
  p1.elapsed_time = next_lap_elapsed(p,length);
  return p1;
}

particle killed_particle(simulation* sim, particle p) {
  p.state = particle_state::DEAD;
  return p;
}

reset_config::reset_config(
  std::function<bool(particle)> should_reset_fn, 
  std::function<particle(simulation*,particle)> reset_particle_fn,
  std::function<particle(simulation*,particle)> killed_particle_fn) {
  this->should_reset_fn=should_reset_fn;
  this->reset_particle_fn=reset_particle_fn;
  this->killed_particle_fn=killed_particle_fn;
}

reset_config::reset_config(
  std::function<bool(particle)> should_reset_fn, 
  std::function<particle(simulation*,particle)> reset_particle_fn) {
  this->should_reset_fn=should_reset_fn;
  this->reset_particle_fn=reset_particle_fn;
  this->killed_particle_fn=killed_particle;
}

uint simulate_reset(simulation* sim, reset_config cfg) {
  uint count = 0;
  for (particle& p : sim->particles) {
    if (cfg.should_reset_fn(p)) {
      p = cfg.reset_particle_fn(sim,p);
      count++;
    } else {
      p = cfg.killed_particle_fn(sim,p);
    }
  }
  return count;
}

std::vector<float> survival_rates(simulation* sim, reset_config cfg) {
  std::vector<float> survival_rates;
  const uint particle_count = sim->particles.size();
  uint prev_survival_count;
  uint survival_count = particle_count;
  do {
    prev_survival_count = survival_count;
    survival_count = simulate_reset(sim,cfg);
    survival_rates.push_back((float)(prev_survival_count - survival_count) / particle_count);
  } while (survival_count > 0);
  return survival_rates;
}

float expected_resets(std::vector<float> reset_probabilities) {
  float expected_resets = 0;
  for (uint i = 0; i < reset_probabilities.size(); i++) {
    expected_resets += i * reset_probabilities[i];
  }
  return expected_resets;
}

std::vector<float> simulate(
  float velocity,
  float initial_wait,
  uint particle_count,
  std::function<float(float)> death_distribution_fn,
  reset_config reset_config) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(initial_wait);
    return survival_rates(&sim,reset_config);
}

void print(float velocity, std::function<std::vector<float>(float)> simulate_fn) {
  std::vector<float> survival_rates = simulate_fn(velocity);
  std::cout << "v=" << std::to_string(velocity) << ":   " 
            << "{expected_resets: " << std::to_string(expected_resets(survival_rates)) << ", " 
            << "distribution: [" <<  stringify_vals(survival_rates) << "]}"
            << std::endl;
}