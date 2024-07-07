#Project Description

#Project TO DOs
- add amenities
- add more tests
- 1000w write up

# Project Compilation Instructions:

cmake -B build/
cmake -Dgtest_force_shared_crt=1 build/
cmake --build build/


# Run the Project:
./build/src/Debug/DreamWorldRoutePlanner_run.exe
# Run the tests:
./build/tests/DreamWorldRoutePlanner_test
