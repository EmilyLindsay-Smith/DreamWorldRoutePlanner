# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.30.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/emily/Documents/tests/DreamWorldRoutePlanner

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/emily/Documents/tests/DreamWorldRoutePlanner/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/flags.make

tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o: tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/flags.make
tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o: /Users/emily/Documents/tests/DreamWorldRoutePlanner/tests/main.cpp
tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o: tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/emily/Documents/tests/DreamWorldRoutePlanner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o"
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o -MF CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o.d -o CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o -c /Users/emily/Documents/tests/DreamWorldRoutePlanner/tests/main.cpp

tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.i"
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/emily/Documents/tests/DreamWorldRoutePlanner/tests/main.cpp > CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.i

tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.s"
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/emily/Documents/tests/DreamWorldRoutePlanner/tests/main.cpp -o CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.s

# Object files for target DreamWorldRoutePlanner_test
DreamWorldRoutePlanner_test_OBJECTS = \
"CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o"

# External object files for target DreamWorldRoutePlanner_test
DreamWorldRoutePlanner_test_EXTERNAL_OBJECTS =

tests/DreamWorldRoutePlanner_test: tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/main.cpp.o
tests/DreamWorldRoutePlanner_test: tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/build.make
tests/DreamWorldRoutePlanner_test: src/libDreamWorldRoutePlanner_lib.a
tests/DreamWorldRoutePlanner_test: lib/libgtest.a
tests/DreamWorldRoutePlanner_test: tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/emily/Documents/tests/DreamWorldRoutePlanner/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DreamWorldRoutePlanner_test"
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DreamWorldRoutePlanner_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/build: tests/DreamWorldRoutePlanner_test
.PHONY : tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/build

tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/clean:
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/DreamWorldRoutePlanner_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/clean

tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/depend:
	cd /Users/emily/Documents/tests/DreamWorldRoutePlanner/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/emily/Documents/tests/DreamWorldRoutePlanner /Users/emily/Documents/tests/DreamWorldRoutePlanner/tests /Users/emily/Documents/tests/DreamWorldRoutePlanner/build /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests /Users/emily/Documents/tests/DreamWorldRoutePlanner/build/tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/DreamWorldRoutePlanner_test.dir/depend

