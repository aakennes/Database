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

# Utility rule file for submit-p3.

# Include any custom commands dependencies for this target.
include CMakeFiles/submit-p3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/submit-p3.dir/progress.make

CMakeFiles/submit-p3:
	cd /home/aakennes/code/database/Database/bustub && zip project3-submission.zip src/include/execution/executors/aggregation_executor.h src/include/execution/executors/delete_executor.h src/include/execution/executors/filter_executor.h src/include/execution/executors/hash_join_executor.h src/include/execution/executors/index_scan_executor.h src/include/execution/executors/insert_executor.h src/include/execution/executors/limit_executor.h src/include/execution/executors/nested_loop_join_executor.h src/include/execution/executors/seq_scan_executor.h src/include/execution/executors/sort_executor.h src/include/execution/executors/topn_executor.h src/include/execution/executors/topn_per_group_executor.h src/include/execution/executors/update_executor.h src/include/execution/executors/window_function_executor.h src/execution/aggregation_executor.cpp src/execution/window_function_executor.cpp src/execution/delete_executor.cpp src/execution/filter_executor.cpp src/execution/hash_join_executor.cpp src/execution/index_scan_executor.cpp src/execution/insert_executor.cpp src/execution/limit_executor.cpp src/execution/nested_loop_join_executor.cpp src/execution/seq_scan_executor.cpp src/execution/sort_executor.cpp src/execution/topn_executor.cpp src/execution/topn_per_group_executor.cpp src/execution/update_executor.cpp src/include/optimizer/optimizer.h src/include/optimizer/optimizer_internal.h src/optimizer/nlj_as_hash_join.cpp src/optimizer/optimizer_custom_rules.cpp src/optimizer/sort_limit_as_topn.cpp src/optimizer/optimizer_internal.cpp src/optimizer/seqscan_as_indexscan.cpp src/common/bustub_ddl.cpp src/include/execution/plans/topn_per_group_plan.h src/include/storage/page/page_guard.h src/storage/page/page_guard.cpp src/include/storage/page/extendible_htable_bucket_page.h src/storage/page/extendible_htable_bucket_page.cpp src/include/storage/page/extendible_htable_directory_page.h src/storage/page/extendible_htable_directory_page.cpp src/include/storage/page/extendible_htable_header_page.h src/storage/page/extendible_htable_header_page.cpp src/include/container/disk/hash/disk_extendible_hash_table.h src/container/disk/hash/disk_extendible_hash_table.cpp src/include/buffer/lru_k_replacer.h src/buffer/lru_k_replacer.cpp src/include/buffer/buffer_pool_manager.h src/buffer/buffer_pool_manager.cpp src/include/storage/disk/disk_scheduler.h src/storage/disk/disk_scheduler.cpp src/storage/page/page_guard.cpp src/include/storage/page/page_guard.h

submit-p3: CMakeFiles/submit-p3
submit-p3: CMakeFiles/submit-p3.dir/build.make
.PHONY : submit-p3

# Rule to build all files generated by this target.
CMakeFiles/submit-p3.dir/build: submit-p3
.PHONY : CMakeFiles/submit-p3.dir/build

CMakeFiles/submit-p3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/submit-p3.dir/cmake_clean.cmake
.PHONY : CMakeFiles/submit-p3.dir/clean

CMakeFiles/submit-p3.dir/depend:
	cd /home/aakennes/code/database/Database/bustub/build_rel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/aakennes/code/database/Database/bustub /home/aakennes/code/database/Database/bustub /home/aakennes/code/database/Database/bustub/build_rel /home/aakennes/code/database/Database/bustub/build_rel /home/aakennes/code/database/Database/bustub/build_rel/CMakeFiles/submit-p3.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/submit-p3.dir/depend

