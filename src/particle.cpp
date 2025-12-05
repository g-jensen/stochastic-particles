#include "../headers/particle.h"

bool particle_does_lap(particle& p, float length) {
  return p.state == particle_state::ALIVE 
         && p.velocity*(p.lifespan - p.initial_wait) >= 2*length;
}