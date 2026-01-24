#include "../headers/strategy.h"
#include "../headers/cli.h"

int main(int argc, char* argv[]) {
  float mean_lifespan = arg_float(argc, argv, "-ml", 2.f);
  float c = arg_float(argc, argv, "-c", 1.f);
  float threshold = c * mean_lifespan;
  
  wait_strategy strategy = make_threshold_strategy(threshold);
  run_strategy_simulation(argc, argv, strategy, "threshold (c=" + std::to_string(c) + ")");
}
