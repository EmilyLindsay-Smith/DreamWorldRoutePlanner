# Project Compilation Instructions:

cmake -B build/
cmake -Dgtest_force_shared_crt=1 build/
cmake --build build/


# Run the Project:
./build/src/Debug/DreamWorldRoutePlanner_run.exe
# Run the tests:
./build/tests/DreamWorldRoutePlanner_test

# To quickly compile and run the tests (after eg change code:)
make RoutePlannerProject_test; tests/RoutePlannerProject_test

