#include "../headers/lap.h"
#include "../headers/io.h"
#include "../headers/cli.h"
#include "../headers/rand.h"

int main(int argc, char* argv[]) {
  int seed = arg_int(argc, argv, "-s", -1);
  seed_random(&seed);
  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  int particle_count = arg_int(argc, argv, "-n", 100000);
  float length = 1.f;

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  auto should_lap_fn = [&](particle p){return particle_does_lap(p,length);};
  auto lap_particle_fn = [&] (simulation* sim, particle p) {return lap_particle(sim,p,length);};

  simulation sim(death_distribution_fn,particle_count,velocity);
  sim.init(0);
  std::vector<float> rates = survival_rates(&sim,lap_config(should_lap_fn,lap_particle_fn));

  float tau = (2 * length) / velocity;
  float total_survival = 0;
  for (const particle& p : sim.particles) {
    total_survival += p.elapsed_time + std::min(p.lifespan, tau);
  }
  float avg_survival_time = total_survival / particle_count;

  std::cout << "{\n"
            << "  \"strategy\": \"none\",\n"
            << "  \"velocity\": " << velocity << ",\n"
            << "  \"tau\": " << (2 * length / velocity) << ",\n"
            << "  \"mean_lifespan\": " << mean_lifespan << ",\n"
            << "  \"lambda\": " << (1.0 / mean_lifespan) << ",\n"
            << "  \"particle_count\": " << particle_count << ",\n"
            << "  \"expected_laps\": " << expected_laps(rates) << ",\n"
            << "  \"avg_survival_time\": " << avg_survival_time << ",\n"
            << "  \"distribution\": " << json_array(rates) << ",\n"
            << "  \"seed\": " << seed << "\n"
            << "}" << std::endl;
}
