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

bool particle_surives(particle& p, float length);