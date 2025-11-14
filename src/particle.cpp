#include "../headers/particle.h"

bool particle_travels_length(particle& p, float length) {
  return p.state == particle_state::ALIVE 
         && p.velocity*(p.lifespan - p.initial_wait) >= length;
}