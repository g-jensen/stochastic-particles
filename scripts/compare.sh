#!/bin/bash

echo "=== resets ==="
./build/resets "$@"
echo ""
echo "=== gates ==="
./build/gates "$@"
echo ""
echo "=== wait_times ==="
./build/wait_times "$@"
