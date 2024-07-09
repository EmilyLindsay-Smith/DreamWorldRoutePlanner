#!/bin/bash

echo "Checking gtest present"

if [ -d "lib/googletest" ]
then
	echo "Googletest installed in lib directory"
else
	mkdir lib
	cd lib
	git clone https://github.com/google/googletest
	cd ..
fi

echo "Starting the build process"

if [ -d "./build" ]
then
	rm -rf build/
	echo "Removed old build directory"
fi

echo ""
echo " Making the build folder... "

cmake -B build/

echo ""
echo " Forcing google test to use same crt as the application... "
cmake -Dgtest_force_shared_crt=1 build/

echo ""
echo " Compiling all the code and tests...."
cmake --build build/

RunExe="./build/src/Debug/DreamWorldRoutePlanner_run.exe"
TestExe="./build/tests/Debug/DreamWorldRoutePlanner_test.exe"

if [ -e $RunExe ]
then
	echo "Application build success"
	echo "To run the application:"
	echo $RunExe
else
	echo "Application build failure"
fi

if [ -e $TestExe ]
then
        echo "Test  build success"
        echo "To run the tests:"
        echo $TextExe
else
        echo "Test build failure"
fi
