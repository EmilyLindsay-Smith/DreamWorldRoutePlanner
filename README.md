# DreamWorld Route Planner

Author	: Dr. Emily Lindsay-Smith	

Version	: 1.0 				

Date 	: July 2024			

## Project Description
This is a C++ project created for Nicholas Day's C++ Part 2: Data Structures and Algorithm course at the Department of Continuing Education, Oxford. . 

## Project Scenario
The route planner creates 100 settlements in a 100x100 unit sized world. 20% of the settlements are large settlements, e.g. citadels; 30% are medium size settlements, e.g. towns; and 50% are small sized settlements, e.g. hamlets.

The route planner generates a road network between the settlements, such that:
	all large settlements are connected by fast roads
	all large and medium settlements are connected by medium roads
	all medium and small settlements are connected by slow roads

The user can interact with the route planner in the following ways:

1) The user can display an alphabetised list of all locations in DreamWorld, and include their settlement type and coordinates
2) The user can search for locations either using the entire string or a substring (prefix).
3) The user can display all available information about a specific location
4) The user can request a path between two locations, and see two routes : one optimised for time and the other for distance
5) The user can request the route to the nearest amenity to a specific location
6) The user can regenerate the settlements and road network in DreamWorld

For details about some of the design decisions, please see DecisionReport.txt

## Project Compilation Instructions:
To compile the project cmake must be installed.


To compile the project, clone this repository, cd into it and run the following commands:

```
cmake -B build/
cmake -Dgtest_force_shared_crt=1 build/
cmake --build build/
```

The second line of the instructions is needed to force googletest to compile with the same CRT as the application
Note to compile the tests, you will need to add a /lib/ directory containing googletest. 
```
mkdir lib
cd lib
git clone https://github.com/google/googletest

```

Alternatively, I have included a bash script to run these commands that can be run as follows:
```
./buildme.sh
```

### Run the Project:
```
./build/src/Debug/DreamWorldRoutePlanner_run.exe
```
### Run the tests:
```
./build/tests/DreamWorldRoutePlanner_test
```
# Future Improvements:
- The PrefixTree could be converted to a radix tree to compress redundant nodes
- The PrefixTree children representation could be changed to a map to avoid iterating over empty values in the current vector
- Facilitate searching for the nearest multiple instances of an amenity
- Add GoogleMock based tests for eg. ContainerEq()
