#pragma once

#include <stdlib.h>
#include <string>

enum class particle_state {
  DEAD = 0,
  ALIVE = 1,
};

struct particle {
  particle_state state;
  float velocity;
  float lifespan;
  float elapsed_time;
  float wait = 0.f;
};

bool particle_does_lap(particle& p, float length);
std::string particle_string(particle p);
float lap_time(particle p, float length);
float next_lap_elapsed(particle p, float length);