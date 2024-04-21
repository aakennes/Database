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

# Include any dependencies generated for this target.
include src/buffer/CMakeFiles/bustub_buffer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/buffer/CMakeFiles/bustub_buffer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/buffer/CMakeFiles/bustub_buffer.dir/progress.make

# Include the compile flags for this target's objects.
include src/buffer/CMakeFiles/bustub_buffer.dir/flags.make

src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/flags.make
src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o: /home/aakennes/code/database/Database/src/buffer/buffer_pool_manager.cpp
src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o -MF CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o.d -o CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o -c /home/aakennes/code/database/Database/src/buffer/buffer_pool_manager.cpp

src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/buffer/buffer_pool_manager.cpp > CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.i

src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/buffer/buffer_pool_manager.cpp -o CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.s

src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/flags.make
src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o: /home/aakennes/code/database/Database/src/buffer/clock_replacer.cpp
src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o -MF CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o.d -o CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o -c /home/aakennes/code/database/Database/src/buffer/clock_replacer.cpp

src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/buffer/clock_replacer.cpp > CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.i

src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/buffer/clock_replacer.cpp -o CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.s

src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/flags.make
src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o: /home/aakennes/code/database/Database/src/buffer/lru_replacer.cpp
src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o -MF CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o.d -o CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o -c /home/aakennes/code/database/Database/src/buffer/lru_replacer.cpp

src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/buffer/lru_replacer.cpp > CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.i

src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/buffer/lru_replacer.cpp -o CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.s

src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/flags.make
src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o: /home/aakennes/code/database/Database/src/buffer/lru_k_replacer.cpp
src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o: src/buffer/CMakeFiles/bustub_buffer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o -MF CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o.d -o CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o -c /home/aakennes/code/database/Database/src/buffer/lru_k_replacer.cpp

src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/buffer/lru_k_replacer.cpp > CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.i

src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/buffer/lru_k_replacer.cpp -o CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.s

bustub_buffer: src/buffer/CMakeFiles/bustub_buffer.dir/buffer_pool_manager.cpp.o
bustub_buffer: src/buffer/CMakeFiles/bustub_buffer.dir/clock_replacer.cpp.o
bustub_buffer: src/buffer/CMakeFiles/bustub_buffer.dir/lru_replacer.cpp.o
bustub_buffer: src/buffer/CMakeFiles/bustub_buffer.dir/lru_k_replacer.cpp.o
bustub_buffer: src/buffer/CMakeFiles/bustub_buffer.dir/build.make
.PHONY : bustub_buffer

# Rule to build all files generated by this target.
src/buffer/CMakeFiles/bustub_buffer.dir/build: bustub_buffer
.PHONY : src/buffer/CMakeFiles/bustub_buffer.dir/build

src/buffer/CMakeFiles/bustub_buffer.dir/clean:
	cd /home/aakennes/code/database/Database/build_rel/src/buffer && $(CMAKE_COMMAND) -P CMakeFiles/bustub_buffer.dir/cmake_clean.cmake
.PHONY : src/buffer/CMakeFiles/bustub_buffer.dir/clean

src/buffer/CMakeFiles/bustub_buffer.dir/depend:
	cd /home/aakennes/code/database/Database/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database /home/aakennes/code/database/Database/src/buffer /home/aakennes/code/database/Database/build_rel /home/aakennes/code/database/Database/build_rel/src/buffer /home/aakennes/code/database/Database/build_rel/src/buffer/CMakeFiles/bustub_buffer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/buffer/CMakeFiles/bustub_buffer.dir/depend

