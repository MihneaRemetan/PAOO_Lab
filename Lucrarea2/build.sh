#!/bin/sh
# Builds both projects in order and runs the application.
set -e
cd "$(dirname "$0")"

echo "=== 1. Library: build + export ==="
cmake -S biblioteca -B biblioteca/build
cmake --build biblioteca/build
cmake --install biblioteca/build

echo "=== 2. Application: build (links libgeometry.a) ==="
cmake -S aplicatie -B aplicatie/build
cmake --build aplicatie/build

echo "=== 3. Run ==="
./aplicatie/build/shapes_app
