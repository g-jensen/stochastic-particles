#include "../headers/lap.h"

particle lap_particle(simulation* sim, particle p, float length) {
  particle p1 = sim->create_particle();
  p1.elapsed_time = next_lap_elapsed(p,length);
  return p1;
}

particle killed_particle(simulation* sim, particle p) {
  p.state = particle_state::DEAD;
  return p;
}

lap_config::lap_config(
  std::function<bool(particle)> should_lap_fn, 
  std::function<particle(simulation*,particle)> lap_particle_fn,
  std::function<particle(simulation*,particle)> killed_particle_fn) {
  this->should_lap_fn=should_lap_fn;
  this->lap_particle_fn=lap_particle_fn;
  this->killed_particle_fn=killed_particle_fn;
}

lap_config::lap_config(
  std::function<bool(particle)> should_lap_fn, 
  std::function<particle(simulation*,particle)> lap_particle_fn) {
  this->should_lap_fn=should_lap_fn;
  this->lap_particle_fn=lap_particle_fn;
  this->killed_particle_fn=killed_particle;
}

uint simulate_lap(simulation* sim, lap_config cfg) {
  uint count = 0;
  for (particle& p : sim->particles) {
    if (cfg.should_lap_fn(p)) {
      p = cfg.lap_particle_fn(sim,p);
      count++;
    } else {
      p = cfg.killed_particle_fn(sim,p);
    }
  }
  return count;
}

std::vector<float> survival_rates(simulation* sim, lap_config cfg) {
  std::vector<float> survival_rates;
  const uint particle_count = sim->particles.size();
  uint prev_survival_count;
  uint survival_count = particle_count;
  do {
    prev_survival_count = survival_count;
    survival_count = simulate_lap(sim,cfg);
    survival_rates.push_back((float)(prev_survival_count - survival_count) / particle_count);
  } while (survival_count > 0);
  return survival_rates;
}

float expected_laps(std::vector<float> lap_probabilities) {
  float result = 0;
  for (uint i = 0; i < lap_probabilities.size(); i++) {
    result += i * lap_probabilities[i];
  }
  return result;
}

std::vector<float> simulate(
  float velocity,
  float initial_wait,
  uint particle_count,
  std::function<float(float)> death_distribution_fn,
  lap_config lap_config) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init(initial_wait);
    return survival_rates(&sim,lap_config);
}

