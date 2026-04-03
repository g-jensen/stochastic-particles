#!/bin/bash

granularities=(24 120)

cargo build --bin basic-generate --bin basic-generate-laps --release
mkdir -p visualize

for granularity in "${granularities[@]}"; do
  echo "Generating granularity=$granularity (lifespan optimization)"
  ./target/release/basic-generate -granularity $granularity
  .venv/bin/python travel_time_lifespan.py output.csv "visualize/$granularity-travel-time-lifespan.png"
  .venv/bin/python lifespan.py output.csv "visualize/$granularity-lifespan.png"

  echo "Generating granularity=$granularity (laps optimization)"
  ./target/release/basic-generate-laps -granularity $granularity
  .venv/bin/python travel_time_laps.py output.csv "visualize/$granularity-travel-time-laps.png"
  .venv/bin/python laps.py output.csv "visualize/$granularity-laps.png"
done
