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

echo "=== no gates, max wait time (upper bound) ==="
./build/max_wait_laps "${args[@]}"
echo ""
echo "=== gates, no wait time (lower bound) ==="
./build/gates "${args[@]}"
echo ""
echo "=== gates, max wait time ==="
./build/late_wait_time "${args[@]}"
echo ""
echo "=== gates, low wait time ==="
./build/early_wait_time "${args[@]}"
echo ""
echo "=== gates, threshold wait time ==="
./build/threshold_wait_time "${args[@]}" -c 1
