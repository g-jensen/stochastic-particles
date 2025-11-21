#include "../headers/reset.h"

uint simulate_reset(simulation& sim, std::function<bool(particle)> should_reset_fn) {
  uint count = 0;
  for (particle& p : sim.particles) {
    if (should_reset_fn(p)) {
      p=sim.create_particle();
      count++;
    } else {
      p.state=particle_state::DEAD;
    }
  }
  return count;
}

std::vector<float> survival_rates(simulation& sim, std::function<bool(particle)> should_reset_fn) {
  std::vector<float> survival_rates;
  const uint particle_count = sim.particles.size();
  uint prev_survival_count;
  uint survival_count = particle_count;
  do {
    prev_survival_count = survival_count;
    survival_count = simulate_reset(sim,should_reset_fn);
    survival_rates.push_back((float)(prev_survival_count - survival_count) / particle_count);
  } while (survival_count > 0);
  return survival_rates;
}