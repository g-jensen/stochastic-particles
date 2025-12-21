#include "../headers/simulation.h"

simulation::simulation(std::function<float(float)> death_distribution_fn, 
                       uint particle_count, 
                       float velocity) {
  this->death_distribution_fn = death_distribution_fn;
  this->particle_count = particle_count;
  this->velocity = velocity;
}

void simulation::init() {
  for (uint i = 0; i < particle_count; i++) {
    particles.push_back(create_particle());
  }
}

void simulation::init(float initial_wait) {
  for (uint i = 0; i < particle_count; i++) {
    particles.push_back(create_particle(initial_wait));
  }
}

void simulation::init(std::function<float(particle)> initial_wait_fn) {
  for (uint i = 0; i < particle_count; i++) {
    particles.push_back(create_particle(initial_wait_fn));
  }
}

particle simulation::create_particle() {
    return {
      .state = particle_state::ALIVE,
      .velocity=velocity,
      .lifespan=death_distribution_fn(random_probability())
    };
  }

particle simulation::create_particle(float initial_wait) {
  particle p = create_particle();
  p.wait = initial_wait;
  return p;
}

particle simulation::create_particle(std::function<float(particle)> initial_wait_fn) {
  particle p = create_particle();
  p.wait = initial_wait_fn(p);
  return p;
}