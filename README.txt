# To compile the project on windowws:

cd build
cmake ..
cmake --build .
make all


ALT:
cmake -B build/
cmake --build build/

cmake .. -DCMAKE_BUILD_TYPE=Debug???


# To run the project: FROM WITHIN BUILD
./src/Debug/RoutePlannerProject_run.exe
#To run the tests:
./tests/RoutePlannerPRoject_test

# To quickly compile and run the tests (after eg change code:)
make RoutePlannerProject_test; tests/RoutePlannerProject_test


Lots  linker errors/warnings?

In build/src/RoutePlannerProject_lib.vcxproj
In build/src/RoutePlannerProject_run.vcxproj

found: <RuntimeLibrary>MultiThreadedDLL</RuntimeLibrary>


In lib/googletest/CMakeCache.txt
	gtest_force_shared_crt:BOOL=OFF
changed to:
	gtest_force_shared_crt:BOOL=ON

In lib/googletest/googletest/CMakeLists.xt
update OFF to ON:
	option(
 	 gtest_force_shared_crt
  	"Use shared (DLL) run-time lib even when Google Test is 		built as static lib."
  	ON)
