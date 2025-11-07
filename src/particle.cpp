#include "../headers/particle.h"

uint particle_surives(particle& p, float length) {
  return p.state == particle_state::ALIVE 
         && p.velocity*p.lifespan >= length;
}