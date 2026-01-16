#include "../headers/gate.h"
#include "../headers/cli.h"
#include "../headers/rand.h"
#include "../headers/io.h"

int main(int argc, char* argv[]) {
  int seed = arg_int(argc, argv, "-s", -1);
  seed_random(seed);
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

  simulation sim(death_distribution_fn,particle_count,velocity);
  sim.init(initial_wait);
  std::vector<float> rates = survival_rates(&sim,reset_config(should_reset_fn,reset_particle_fn));

  std::cout << "{\n"
            << "  \"velocity\": " << velocity << ",\n"
            << "  \"mean_lifespan\": " << mean_lifespan << ",\n"
            << "  \"initial_wait\": " << initial_wait << ",\n"
            << "  \"gate_starting_state\": " << (starting_state ? "true" : "false") << ",\n"
            << "  \"gate_t1\": " << t1 << ",\n"
            << "  \"gate_t2\": " << t2 << ",\n"
            << "  \"expected_resets\": " << expected_resets(rates) << ",\n"
            << "  \"distribution\": " << json_array(rates) << "\n"
            << "}" << std::endl;
}
