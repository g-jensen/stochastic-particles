#!/bin/bash

seed=""
args=()

for ((i=1; i<=$#; i++)); do
  arg="${!i}"
  if [[ "$arg" == "-s" ]]; then
    next=$((i+1))
    seed="${!next}"
  fi
  args+=("$arg")
done

if [[ -z "$seed" ]]; then
  seed=$((RANDOM % 1000000))
  args+=("-s" "$seed")
fi

echo "=== max_wait_laps (upper bound) ==="
./build/max_wait_laps "${args[@]}"
echo ""
echo "=== gates (lower bound) ==="
./build/gates "${args[@]}"
echo ""
echo "=== late_wait_time ==="
./build/late_wait_time "${args[@]}"
echo ""
echo "=== early_wait_time ==="
./build/early_wait_time "${args[@]}"
echo ""
echo "=== threshold_wait_time ==="
./build/threshold_wait_time "${args[@]}" -c 1
