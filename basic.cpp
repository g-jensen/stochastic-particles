#include <iostream>
#include <functional>
#include <cmath>
#include <random>
#include <vector>

// Inverse of f(t) = 1 - e^{-t/mean}.
float exponential_distribution(float rand, float mean) {
  return -mean * log(1-rand);
}

std::uniform_real_distribution<> dis(0.0, 1.0);
std::random_device rd;
std::mt19937 gen(rd());
float random_probability() {
  return dis(gen);
}

struct particle {
  float x;
  float lifespan;
};

class simulation {
public:
  // assumes 0 <= input <= 1 and 0 <= output <= inf
  std::function<float(float)> death_distribution_fn;
  std::vector<particle> particles;
  
  simulation(std::function<float(float)> death_distribution_fn, uint particle_count) {
    this->death_distribution_fn = death_distribution_fn;
    for (uint i = 0; i < particle_count; i++) {
      particle p = {.x=0, .lifespan=death_distribution_fn(random_probability())};
      particles.push_back(p);
    }
  }

  float averge_lifespan() {
    float lifespan_sum = 0;
    for (particle& p : particles) {
      lifespan_sum += p.lifespan;
    }
    return lifespan_sum / particles.size();
  }
};

int main() {
  float mean = 1.f;
  auto death_distribution_fn = [mean](float rand) {return exponential_distribution(rand,mean);};
  int particle_count = 1000;

  simulation sim(death_distribution_fn,particle_count);
  std::cout << sim.averge_lifespan() << std::endl;
}