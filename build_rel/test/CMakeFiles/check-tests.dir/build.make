# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /home/aakennes/.local/lib/python3.10/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/aakennes/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/aakennes/code/database/Database

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aakennes/code/database/Database/build_rel

# Utility rule file for check-tests.

# Include any custom commands dependencies for this target.
include test/CMakeFiles/check-tests.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/check-tests.dir/progress.make

test/CMakeFiles/check-tests:
	cd /home/aakennes/code/database/Database/build_rel/test && /home/aakennes/.local/lib/python3.10/site-packages/cmake/data/bin/ctest --verbose

check-tests: test/CMakeFiles/check-tests
check-tests: test/CMakeFiles/check-tests.dir/build.make
.PHONY : check-tests

# Rule to build all files generated by this target.
test/CMakeFiles/check-tests.dir/build: check-tests
.PHONY : test/CMakeFiles/check-tests.dir/build

test/CMakeFiles/check-tests.dir/clean:
	cd /home/aakennes/code/database/Database/build_rel/test && $(CMAKE_COMMAND) -P CMakeFiles/check-tests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/check-tests.dir/clean

test/CMakeFiles/check-tests.dir/depend:
	cd /home/aakennes/code/database/Database/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database /home/aakennes/code/database/Database/test /home/aakennes/code/database/Database/build_rel /home/aakennes/code/database/Database/build_rel/test /home/aakennes/code/database/Database/build_rel/test/CMakeFiles/check-tests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/check-tests.dir/depend

