#include "../headers/reset.h"
#include "../headers/io.h"
#include "../headers/cli.h"

int main(int argc, char* argv[]) {
  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
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
  print_fn(velocity);
}