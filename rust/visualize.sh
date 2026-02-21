#!/bin/bash

granularities=(20 50 100 200 300 400)

cargo build --bin basic-generate --release
mkdir -p visualize

for granularity in "${granularities[@]}"; do
  echo "Generating granularity=$granularity"
  ./target/release/basic-generate -granularity $granularity
  .venv/bin/python travel_time.py output.csv "visualize/$granularity-travel-time.png"
  .venv/bin/python lifespan.py output.csv "visualize/$granularity-lifespan.png"
done