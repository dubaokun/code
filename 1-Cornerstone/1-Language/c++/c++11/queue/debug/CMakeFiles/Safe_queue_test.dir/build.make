# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dubaokun/github/code/basic/c++/c++11/queue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dubaokun/github/code/basic/c++/c++11/queue/debug

# Include any dependencies generated for this target.
include CMakeFiles/Safe_queue_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Safe_queue_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Safe_queue_test.dir/flags.make

CMakeFiles/Safe_queue_test.dir/src/main.cpp.o: CMakeFiles/Safe_queue_test.dir/flags.make
CMakeFiles/Safe_queue_test.dir/src/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dubaokun/github/code/basic/c++/c++11/queue/debug/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Safe_queue_test.dir/src/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Safe_queue_test.dir/src/main.cpp.o -c /home/dubaokun/github/code/basic/c++/c++11/queue/src/main.cpp

CMakeFiles/Safe_queue_test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Safe_queue_test.dir/src/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dubaokun/github/code/basic/c++/c++11/queue/src/main.cpp > CMakeFiles/Safe_queue_test.dir/src/main.cpp.i

CMakeFiles/Safe_queue_test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Safe_queue_test.dir/src/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dubaokun/github/code/basic/c++/c++11/queue/src/main.cpp -o CMakeFiles/Safe_queue_test.dir/src/main.cpp.s

CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.requires:
.PHONY : CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.requires

CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.provides: CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Safe_queue_test.dir/build.make CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.provides

CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.provides.build: CMakeFiles/Safe_queue_test.dir/src/main.cpp.o

# Object files for target Safe_queue_test
Safe_queue_test_OBJECTS = \
"CMakeFiles/Safe_queue_test.dir/src/main.cpp.o"

# External object files for target Safe_queue_test
Safe_queue_test_EXTERNAL_OBJECTS =

Safe_queue_test: CMakeFiles/Safe_queue_test.dir/src/main.cpp.o
Safe_queue_test: CMakeFiles/Safe_queue_test.dir/build.make
Safe_queue_test: CMakeFiles/Safe_queue_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Safe_queue_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Safe_queue_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Safe_queue_test.dir/build: Safe_queue_test
.PHONY : CMakeFiles/Safe_queue_test.dir/build

CMakeFiles/Safe_queue_test.dir/requires: CMakeFiles/Safe_queue_test.dir/src/main.cpp.o.requires
.PHONY : CMakeFiles/Safe_queue_test.dir/requires

CMakeFiles/Safe_queue_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Safe_queue_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Safe_queue_test.dir/clean

CMakeFiles/Safe_queue_test.dir/depend:
	cd /home/dubaokun/github/code/basic/c++/c++11/queue/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dubaokun/github/code/basic/c++/c++11/queue /home/dubaokun/github/code/basic/c++/c++11/queue /home/dubaokun/github/code/basic/c++/c++11/queue/debug /home/dubaokun/github/code/basic/c++/c++11/queue/debug /home/dubaokun/github/code/basic/c++/c++11/queue/debug/CMakeFiles/Safe_queue_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Safe_queue_test.dir/depend
