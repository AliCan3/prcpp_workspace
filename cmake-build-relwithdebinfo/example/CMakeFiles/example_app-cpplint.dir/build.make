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
CMAKE_BINARY_DIR = /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo

# Utility rule file for example_app-cpplint.

# Include the progress variables for this target.
include example/CMakeFiles/example_app-cpplint.dir/progress.make

example/CMakeFiles/example_app-cpplint: example/cpplint/src/main.cpp.timestamp


example/cpplint/src/main.cpp.timestamp: ../example/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linting with cpplint: /home/vagrant/prcpp/workspace/example/src/main.cpp"
	cd /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/example && /home/vagrant/clion-2020.2/bin/cmake/linux/bin/cmake -E chdir /home/vagrant/prcpp/workspace /usr/bin/python /home/vagrant/prcpp/workspace/cmake/cpplint.py --filter=-legal/copyright,-build/c++11,-build/c++14,-whitespace/comments,-build/include, --counting=toplevel --extensions=cc,cpp,cxx,h,hpp,hxx --headers=h,hpp,hxx --linelength=120 --quiet /home/vagrant/prcpp/workspace/example/src/main.cpp && touch /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/example/cpplint/src/main.cpp.timestamp

example_app-cpplint: example/CMakeFiles/example_app-cpplint
example_app-cpplint: example/cpplint/src/main.cpp.timestamp
example_app-cpplint: example/CMakeFiles/example_app-cpplint.dir/build.make

.PHONY : example_app-cpplint

# Rule to build all files generated by this target.
example/CMakeFiles/example_app-cpplint.dir/build: example_app-cpplint

.PHONY : example/CMakeFiles/example_app-cpplint.dir/build

example/CMakeFiles/example_app-cpplint.dir/clean:
	cd /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/example && $(CMAKE_COMMAND) -P CMakeFiles/example_app-cpplint.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/example_app-cpplint.dir/clean

example/CMakeFiles/example_app-cpplint.dir/depend:
	cd /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/prcpp/workspace /home/vagrant/prcpp/workspace/example /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/example /home/vagrant/prcpp/workspace/cmake-build-relwithdebinfo/example/CMakeFiles/example_app-cpplint.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/example_app-cpplint.dir/depend
