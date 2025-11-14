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
  float initial_wait = 0.f;
};

bool particle_travels_length(particle& p, float length);