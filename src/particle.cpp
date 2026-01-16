#include "../headers/particle.h"

bool particle_does_lap(particle p, float length) {
  return p.state == particle_state::ALIVE 
         && p.velocity*(p.lifespan - p.wait) >= 2*length;
}

std::string particle_string(particle p) {
  std::string s = "";
  s += "{";
  s += "vel:" + std::to_string(p.velocity) + ", ";
  s += "life:" + std::to_string(p.lifespan) + ", ";
  s += "wait: " + std::to_string(p.wait) + ", ";
  s += "t: " + std::to_string(p.elapsed_time) + ", ";
  s += "state:" + std::to_string((int)p.state);
  s += "}";
  return s;
}

float lap_time(particle p, float length) {
  return (2*length / p.velocity);
}

float next_lap_elapsed(particle p, float length) {
  return p.elapsed_time + p.wait + lap_time(p, length);
}