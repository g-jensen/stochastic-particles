#include <iostream>
#include "../headers/distribution.h"
#include "../headers/simulation.h"
#include "../headers/io.h"

uint simulate_reset(simulation& sim, float length) {
  uint count = 0;
  for (particle& p : sim.particles) {
    if (particle_surives(p,length)) {
      p=sim.create_particle();
      count++;
    } else {
      p.state=particle_state::DEAD;
    }
  }
  return count;
}

std::vector<float> survival_rates(simulation& sim, float length) {
  std::vector<float> survival_rates;
  const uint particle_count = sim.particles.size();
  uint prev_survival_count;
  uint survival_count = particle_count;
  do {
    prev_survival_count = survival_count;
    survival_count = simulate_reset(sim,length);
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

int main() {
  float mean_lifespan = 1.f;
  float length = 1.f;
  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  int particle_count = 1000000;

  auto simulate_fn = [&](float velocity) {
    simulation sim(death_distribution_fn,particle_count,velocity);
    sim.init();
    return survival_rates(sim,length);
  };

  auto print_fn = [&](float velocity) {
    std::vector<float> survival_rates = simulate_fn(velocity);
    std::cout << "v=" << std::to_string(velocity) << ":   " 
              << "{expected_resets: " << std::to_string(expected_resets(survival_rates)) << ", " 
              << "distribution: [" <<  stringify_vals(survival_rates) << "]}"
              << std::endl;
  };

  std::cout << "Resets with mean lifespan " << mean_lifespan <<  " and velocity v:" << std::endl;
  print_fn(0.f);
  print_fn(0.25f);
  print_fn(0.5f);
  print_fn(1.f);
  print_fn(2.f);

  // for (float v = 0; v < 20; v += 0.25) {
  //   std::vector<float> survival_rates = simulate_fn(v);
  //   std::cout << "(" << v << ", " << std::to_string(expected_resets(survival_rates)) << ")" << std::endl;
  // }
}

/* Sample Output:

Resets with mean lifespan 1 and velocity v:
v=0.000000:   {expected_resets: 0.000000},{distribution: [1.000000]}
v=0.250000:   {expected_resets: 0.018635},{distribution: [0.981707, 0.017957, 0.000330, 0.000006, 0.000000]}
v=0.500000:   {expected_resets: 0.156528},{distribution: [0.864668, 0.117002, 0.015851, 0.002144, 0.000290, 0.000039, 0.000006, 0.000001, 0.000000]}
v=1.000000:   {expected_resets: 0.581934},{distribution: [0.632176, 0.232496, 0.085524, 0.031490, 0.011581, 0.004247, 0.001569, 0.000582, 0.000213, 0.000077, 0.000029, 0.000011, 0.000004, 0.000001, 0.000001, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000]}
v=2.000000:   {expected_resets: 1.541473},{distribution: [0.393504, 0.238652, 0.144690, 0.087821, 0.053232, 0.032317, 0.019598, 0.011880, 0.007195, 0.004371, 0.002645, 0.001609, 0.000976, 0.000590, 0.000363, 0.000217, 0.000135, 0.000082, 0.000048, 0.000030, 0.000018, 0.000011, 0.000006, 0.000004, 0.000002, 0.000001, 0.000001, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000]}

*/