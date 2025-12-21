#include "../headers/reset.h"

particle reset_particle(simulation* sim, particle) {
  return sim->create_particle();
}

particle killed_particle(simulation* sim, particle p) {
  p.state = particle_state::DEAD;
  return p;
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