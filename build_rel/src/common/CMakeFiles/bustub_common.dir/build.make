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
include src/common/CMakeFiles/bustub_common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/common/CMakeFiles/bustub_common.dir/compiler_depend.make

# Include the progress variables for this target.
include src/common/CMakeFiles/bustub_common.dir/progress.make

# Include the compile flags for this target's objects.
include src/common/CMakeFiles/bustub_common.dir/flags.make

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o: /home/aakennes/code/database/Database/src/common/bustub_instance.cpp
src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o: src/common/CMakeFiles/bustub_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o -MF CMakeFiles/bustub_common.dir/bustub_instance.cpp.o.d -o CMakeFiles/bustub_common.dir/bustub_instance.cpp.o -c /home/aakennes/code/database/Database/src/common/bustub_instance.cpp

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/bustub_instance.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/common/bustub_instance.cpp > CMakeFiles/bustub_common.dir/bustub_instance.cpp.i

src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/bustub_instance.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/common/bustub_instance.cpp -o CMakeFiles/bustub_common.dir/bustub_instance.cpp.s

src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o: /home/aakennes/code/database/Database/src/common/bustub_ddl.cpp
src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o: src/common/CMakeFiles/bustub_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o -MF CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o.d -o CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o -c /home/aakennes/code/database/Database/src/common/bustub_ddl.cpp

src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/bustub_ddl.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/common/bustub_ddl.cpp > CMakeFiles/bustub_common.dir/bustub_ddl.cpp.i

src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/bustub_ddl.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/common/bustub_ddl.cpp -o CMakeFiles/bustub_common.dir/bustub_ddl.cpp.s

src/common/CMakeFiles/bustub_common.dir/config.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/config.cpp.o: /home/aakennes/code/database/Database/src/common/config.cpp
src/common/CMakeFiles/bustub_common.dir/config.cpp.o: src/common/CMakeFiles/bustub_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/common/CMakeFiles/bustub_common.dir/config.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/common/CMakeFiles/bustub_common.dir/config.cpp.o -MF CMakeFiles/bustub_common.dir/config.cpp.o.d -o CMakeFiles/bustub_common.dir/config.cpp.o -c /home/aakennes/code/database/Database/src/common/config.cpp

src/common/CMakeFiles/bustub_common.dir/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/config.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/common/config.cpp > CMakeFiles/bustub_common.dir/config.cpp.i

src/common/CMakeFiles/bustub_common.dir/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/config.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/common/config.cpp -o CMakeFiles/bustub_common.dir/config.cpp.s

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o: src/common/CMakeFiles/bustub_common.dir/flags.make
src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o: /home/aakennes/code/database/Database/src/common/util/string_util.cpp
src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o: src/common/CMakeFiles/bustub_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/aakennes/code/database/Database/build_rel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o -MF CMakeFiles/bustub_common.dir/util/string_util.cpp.o.d -o CMakeFiles/bustub_common.dir/util/string_util.cpp.o -c /home/aakennes/code/database/Database/src/common/util/string_util.cpp

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bustub_common.dir/util/string_util.cpp.i"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/aakennes/code/database/Database/src/common/util/string_util.cpp > CMakeFiles/bustub_common.dir/util/string_util.cpp.i

src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bustub_common.dir/util/string_util.cpp.s"
	cd /home/aakennes/code/database/Database/build_rel/src/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/aakennes/code/database/Database/src/common/util/string_util.cpp -o CMakeFiles/bustub_common.dir/util/string_util.cpp.s

bustub_common: src/common/CMakeFiles/bustub_common.dir/bustub_instance.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/bustub_ddl.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/config.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/util/string_util.cpp.o
bustub_common: src/common/CMakeFiles/bustub_common.dir/build.make
.PHONY : bustub_common

# Rule to build all files generated by this target.
src/common/CMakeFiles/bustub_common.dir/build: bustub_common
.PHONY : src/common/CMakeFiles/bustub_common.dir/build

src/common/CMakeFiles/bustub_common.dir/clean:
	cd /home/aakennes/code/database/Database/build_rel/src/common && $(CMAKE_COMMAND) -P CMakeFiles/bustub_common.dir/cmake_clean.cmake
.PHONY : src/common/CMakeFiles/bustub_common.dir/clean

src/common/CMakeFiles/bustub_common.dir/depend:
	cd /home/aakennes/code/database/Database/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database /home/aakennes/code/database/Database/src/common /home/aakennes/code/database/Database/build_rel /home/aakennes/code/database/Database/build_rel/src/common /home/aakennes/code/database/Database/build_rel/src/common/CMakeFiles/bustub_common.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/common/CMakeFiles/bustub_common.dir/depend

