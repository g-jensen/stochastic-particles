#!/bin/bash

echo "=== resets (upper bound) ==="
./build/resets "$@"
echo ""
echo "=== late_wait_time ==="
./build/late_wait_time "$@"
echo ""
echo "=== early_wait_time ==="
./build/early_wait_time "$@"
