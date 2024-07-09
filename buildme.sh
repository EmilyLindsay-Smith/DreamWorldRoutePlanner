#!/bin/bash

echo "Starting the build process"

rm -rf build/

echo ""
echo " Making the build folder... "

cmake -B build/

echo ""
echo " Forcing google test to use same crt as the application... "
cmake -Dgtest_force_shared_crt=1 build/

echo ""
echo " Compiling all the code and tests...."
cmake --build build/

echo ""
echo "Build complete"
echo ""
echo "To run the application:"
echo " ./build/src/Debug/DreamWorldRoutePlanner_run.exe"
echo ""
echo "To run the tests:"
echo " ./build/tests/Debug/DreamWorldRoutePlanner_test.exe"

