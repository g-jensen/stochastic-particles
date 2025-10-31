#pragma once

#include <stdlib.h>

enum class particle_state {
  DEAD = 0,
  ALIVE = 1,
};

struct particle {
  particle_state state;
  float velocity;
  float lifespan;
};

uint particle_surives(particle& p, float length) {
  return p.state == particle_state::ALIVE 
         && p.velocity*p.lifespan >= length;
}