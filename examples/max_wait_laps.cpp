#include "../headers/lap.h"
#include "../headers/io.h"
#include "../headers/cli.h"
#include "../headers/rand.h"

particle lap_particle_max_wait(simulation* sim, particle p, float length) {
  particle p1 = sim->create_particle();
  float tau = (2 * length) / p.velocity;
  float wait = std::max(0.f, p.lifespan - tau);
  p1.elapsed_time = p.elapsed_time + wait + tau;
  p1.wait = std::max(0.f, p1.lifespan - tau);
  return p1;
}

int main(int argc, char* argv[]) {
  int seed = arg_int(argc, argv, "-s", -1);
  seed_random(&seed);
  float velocity = arg_float(argc, argv, "-v", 1.f);
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  int particle_count = arg_int(argc, argv, "-n", 100000);
  float length = 1.f;
  float tau = (2 * length) / velocity;

  auto death_distribution_fn = [&](float rand) {return exponential_distribution(rand,mean_lifespan);};
  auto should_lap_fn = [&](particle p){return particle_does_lap(p,length);};
  auto lap_particle_fn = [&](simulation* sim, particle p) {return lap_particle_max_wait(sim,p,length);};

  simulation sim(death_distribution_fn,particle_count,velocity);
  for (int i = 0; i < particle_count; i++) {
    particle p = sim.create_particle();
    p.wait = std::max(0.f, p.lifespan - tau);
    sim.particles.push_back(p);
  }
  std::vector<float> rates = survival_rates(&sim,lap_config(should_lap_fn,lap_particle_fn));

  float total_survival = 0;
  for (const particle& p : sim.particles) {
    total_survival += p.elapsed_time + std::min(p.lifespan, p.wait + tau);
  }
  float avg_survival_time = total_survival / particle_count;

  std::cout << "{\n"
            << "  \"strategy\": \"max_wait\",\n"
            << "  \"velocity\": " << velocity << ",\n"
            // << "  \"tau\": " << tau << ",\n"
            << "  \"mean_lifespan\": " << mean_lifespan << ",\n"
            // << "  \"lambda\": " << (1.0 / mean_lifespan) << ",\n"
            << "  \"particle_count\": " << particle_count << ",\n"
            << "  \"expected_laps\": " << expected_laps(rates) << ",\n"
            << "  \"avg_survival_time\": " << avg_survival_time << ",\n"
            << "  \"distribution\": " << json_array(rates) << ",\n"
            << "  \"seed\": " << seed << "\n"
            << "}" << std::endl;
}
