#include "../headers/gate.h"
#include "../headers/cli.h"

int main(int argc, char* argv[]) {
  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  float initial_wait = arg_float(argc, argv, "-w", 0.f);
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

  auto reset_particle_fn = [&] (simulation* sim, particle p) {return reset_particle(sim,p,length);};

  auto simulate_fn = [&](float velocity, float initial_wait) {
    return simulate(velocity,initial_wait,particle_count,death_distribution_fn,reset_config(should_reset_fn,reset_particle_fn));
  };

  auto print_fn = [&](float velocity, float initial_wait) {
    print(velocity,initial_wait,simulate_fn);
  };

  std::cout << "Resets with mean lifespan " << mean_lifespan << ", gate " << gate_to_string(g) << ", and velocity v:" << std::endl;
  print_fn(velocity, initial_wait);
}