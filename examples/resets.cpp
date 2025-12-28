#include "../headers/reset.h"
#include "../headers/io.h"

int main() {
  float mean_lifespan = 2.f;
  float length = 1.f;
  int particle_count = 1000000;

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  auto should_reset_fn = [&](particle p){return particle_does_lap(p,length);};
  auto reset_particle_fn = [&] (simulation* sim, particle p) {return reset_particle(sim,p,length);};

  auto simulate_fn = [&](float velocity) {
    return simulate(velocity,0,particle_count,death_distribution_fn,reset_config(should_reset_fn,reset_particle_fn));
  };

  auto print_fn = [&](float velocity) {print(velocity,simulate_fn);};

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