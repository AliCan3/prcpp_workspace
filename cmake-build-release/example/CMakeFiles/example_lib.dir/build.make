# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /home/vagrant/clion-2020.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/vagrant/clion-2020.2/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vagrant/prcpp/workspace

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vagrant/prcpp/workspace/cmake-build-release

# Include any dependencies generated for this target.
include example/CMakeFiles/example_lib.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/example_lib.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/example_lib.dir/flags.make

example/CMakeFiles/example_lib.dir/src/function.cpp.o: example/CMakeFiles/example_lib.dir/flags.make
example/CMakeFiles/example_lib.dir/src/function.cpp.o: ../example/src/function.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vagrant/prcpp/workspace/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/example_lib.dir/src/function.cpp.o"
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && /usr/bin/ccache /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/example_lib.dir/src/function.cpp.o -c /home/vagrant/prcpp/workspace/example/src/function.cpp

example/CMakeFiles/example_lib.dir/src/function.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/example_lib.dir/src/function.cpp.i"
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vagrant/prcpp/workspace/example/src/function.cpp > CMakeFiles/example_lib.dir/src/function.cpp.i

example/CMakeFiles/example_lib.dir/src/function.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/example_lib.dir/src/function.cpp.s"
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vagrant/prcpp/workspace/example/src/function.cpp -o CMakeFiles/example_lib.dir/src/function.cpp.s

# Object files for target example_lib
example_lib_OBJECTS = \
"CMakeFiles/example_lib.dir/src/function.cpp.o"

# External object files for target example_lib
example_lib_EXTERNAL_OBJECTS =

example/libexample_lib.a: example/CMakeFiles/example_lib.dir/src/function.cpp.o
example/libexample_lib.a: example/CMakeFiles/example_lib.dir/build.make
example/libexample_lib.a: example/CMakeFiles/example_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vagrant/prcpp/workspace/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libexample_lib.a"
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && $(CMAKE_COMMAND) -P CMakeFiles/example_lib.dir/cmake_clean_target.cmake
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/example_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/example_lib.dir/build: example/libexample_lib.a

.PHONY : example/CMakeFiles/example_lib.dir/build

example/CMakeFiles/example_lib.dir/clean:
	cd /home/vagrant/prcpp/workspace/cmake-build-release/example && $(CMAKE_COMMAND) -P CMakeFiles/example_lib.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/example_lib.dir/clean

example/CMakeFiles/example_lib.dir/depend:
	cd /home/vagrant/prcpp/workspace/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/prcpp/workspace /home/vagrant/prcpp/workspace/example /home/vagrant/prcpp/workspace/cmake-build-release /home/vagrant/prcpp/workspace/cmake-build-release/example /home/vagrant/prcpp/workspace/cmake-build-release/example/CMakeFiles/example_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/example_lib.dir/depend
