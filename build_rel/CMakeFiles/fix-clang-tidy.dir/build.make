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

# Utility rule file for fix-clang-tidy.

# Include any custom commands dependencies for this target.
include CMakeFiles/fix-clang-tidy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/fix-clang-tidy.dir/progress.make

CMakeFiles/fix-clang-tidy:
	/home/aakennes/code/database/Database/build_support/run_clang_tidy.py -clang-tidy-binary /usr/bin/clang-tidy-14 -p /home/aakennes/code/database/Database/build_rel -clang-apply-replacements-binary /usr/bin/clang-apply-replacements-14 -fix

fix-clang-tidy: CMakeFiles/fix-clang-tidy
fix-clang-tidy: CMakeFiles/fix-clang-tidy.dir/build.make
.PHONY : fix-clang-tidy

# Rule to build all files generated by this target.
CMakeFiles/fix-clang-tidy.dir/build: fix-clang-tidy
.PHONY : CMakeFiles/fix-clang-tidy.dir/build

CMakeFiles/fix-clang-tidy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/fix-clang-tidy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/fix-clang-tidy.dir/clean

CMakeFiles/fix-clang-tidy.dir/depend:
	cd /home/aakennes/code/database/Database/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database /home/aakennes/code/database/Database /home/aakennes/code/database/Database/build_rel /home/aakennes/code/database/Database/build_rel /home/aakennes/code/database/Database/build_rel/CMakeFiles/fix-clang-tidy.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/fix-clang-tidy.dir/depend

