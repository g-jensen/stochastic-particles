#include "../headers/cli.h"
#include "../headers/math.h"
#include <iostream>

bool should_pass_lap(float phase, uint lap_count, float travel_time, float on_ratio) {
  return mod(phase+(lap_count*travel_time),1) <= on_ratio;
}

uint max_laps(float phase, float travel_time, float on_ratio) {
  uint laps = 0;
  while (should_pass_lap(phase, laps, travel_time, on_ratio)) {
    laps++;
  }
  return laps;
}

int main(int argc, char* argv[]) {
  float phase = arg_float(argc,argv,"-phase",0.f);
  float on_ratio = arg_float(argc,argv,"-on-ratio",0.5f);
  float travel_time = arg_float(argc,argv,"-travel-time",1.f);

  std::cout << max_laps(phase, travel_time, on_ratio) << std::endl;
}