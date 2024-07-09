#!/bin/bash

echo "Starting the build process"

rm -rf build/
cmake -B build/
cmake -Dgtest_force_shared_crt=1 build/
cmake --build build/

echo "Build complete"
