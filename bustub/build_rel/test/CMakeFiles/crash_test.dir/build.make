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
CMAKE_SOURCE_DIR = /home/aakennes/code/database/Database/bustub

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/aakennes/code/database/Database/bustub/build_rel

# Include any dependencies generated for this target.
include test/CMakeFiles/crash_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include test/CMakeFiles/crash_test.dir/compiler_depend.make

# Include the progress variables for this target.
include test/CMakeFiles/crash_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/crash_test.dir/flags.make

test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o: test/CMakeFiles/crash_test.dir/flags.make
test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o: /home/aakennes/code/database/Database/bustub/test/backtrace/crash_test.cpp
test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o: test/CMakeFiles/crash_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/bustub/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o -MF CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o.d -o CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o -c /home/aakennes/code/database/Database/bustub/test/backtrace/crash_test.cpp

test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.i"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/bustub/test/backtrace/crash_test.cpp > CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.i

test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.s"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/bustub/test/backtrace/crash_test.cpp -o CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.s

test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o: test/CMakeFiles/crash_test.dir/flags.make
test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o: /home/aakennes/code/database/Database/bustub/tools/backtrace.cpp
test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o: test/CMakeFiles/crash_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/bustub/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o -MF CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o.d -o CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o -c /home/aakennes/code/database/Database/bustub/tools/backtrace.cpp

test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.i"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/bustub/tools/backtrace.cpp > CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.i

test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.s"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/bustub/tools/backtrace.cpp -o CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.s

# Object files for target crash_test
crash_test_OBJECTS = \
"CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o" \
"CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o"

# External object files for target crash_test
crash_test_EXTERNAL_OBJECTS =

test/crash_test: test/CMakeFiles/crash_test.dir/backtrace/crash_test.cpp.o
test/crash_test: test/CMakeFiles/crash_test.dir/__/tools/backtrace.cpp.o
test/crash_test: test/CMakeFiles/crash_test.dir/build.make
test/crash_test: /usr/lib/x86_64-linux-gnu/libdwarf.so
test/crash_test: /usr/lib/x86_64-linux-gnu/libelf.so
test/crash_test: /usr/lib/x86_64-linux-gnu/libdl.a
test/crash_test: lib/libbustub.a
test/crash_test: lib/libgtest.a
test/crash_test: lib/libgmock_main.a
test/crash_test: lib/libbustub_murmur3.a
test/crash_test: lib/libduckdb_pg_query.a
test/crash_test: lib/libfmt.a
test/crash_test: lib/libfort.a
test/crash_test: lib/libgmock.a
test/crash_test: lib/libgtest.a
test/crash_test: test/CMakeFiles/crash_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/aakennes/code/database/Database/bustub/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable crash_test"
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/crash_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && /home/aakennes/.local/lib/python3.10/site-packages/cmake/data/bin/cmake -D TEST_TARGET=crash_test -D TEST_EXECUTABLE=/home/aakennes/code/database/Database/bustub/build_rel/test/crash_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/aakennes/code/database/Database/bustub/build_rel/test -D "TEST_EXTRA_ARGS=--gtest_output=xml:/home/aakennes/code/database/Database/bustub/build_rel/test/crash_test.xml;--gtest_catch_exceptions=0" -D "TEST_PROPERTIES=TIMEOUT;120" -D TEST_PREFIX= -D TEST_SUFFIX= -D TEST_FILTER= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=crash_test_TESTS -D CTEST_FILE=/home/aakennes/code/database/Database/bustub/build_rel/test/crash_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=120 -D TEST_XML_OUTPUT_DIR= -P /home/aakennes/.local/lib/python3.10/site-packages/cmake/data/share/cmake-3.27/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/crash_test.dir/build: test/crash_test
.PHONY : test/CMakeFiles/crash_test.dir/build

test/CMakeFiles/crash_test.dir/clean:
	cd /home/aakennes/code/database/Database/bustub/build_rel/test && $(CMAKE_COMMAND) -P CMakeFiles/crash_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/crash_test.dir/clean

test/CMakeFiles/crash_test.dir/depend:
	cd /home/aakennes/code/database/Database/bustub/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database/bustub /home/aakennes/code/database/Database/bustub/test /home/aakennes/code/database/Database/bustub/build_rel /home/aakennes/code/database/Database/bustub/build_rel/test /home/aakennes/code/database/Database/bustub/build_rel/test/CMakeFiles/crash_test.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : test/CMakeFiles/crash_test.dir/depend

