#pragma once

#include <stdlib.h>

struct particle {
  float velocity;
  float lifespan;
};

uint particle_surives(particle& p, float length) {
  return p.velocity*p.lifespan >= length;
}