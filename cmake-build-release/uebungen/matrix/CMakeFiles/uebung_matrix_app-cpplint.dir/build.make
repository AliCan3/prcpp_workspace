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

# Utility rule file for uebung_matrix_app-cpplint.

# Include the progress variables for this target.
include uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/progress.make

uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint: uebungen/matrix/cpplint/src/main.cpp.timestamp


uebungen/matrix/cpplint/src/main.cpp.timestamp: ../uebungen/matrix/src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/vagrant/prcpp/workspace/cmake-build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linting with cpplint: /home/vagrant/prcpp/workspace/uebungen/matrix/src/main.cpp"
	cd /home/vagrant/prcpp/workspace/cmake-build-release/uebungen/matrix && /home/vagrant/clion-2020.2/bin/cmake/linux/bin/cmake -E chdir /home/vagrant/prcpp/workspace /usr/bin/python /home/vagrant/prcpp/workspace/cmake/cpplint.py --filter=-legal/copyright,-build/c++11,-build/c++14,-whitespace/comments,-build/include, --counting=toplevel --extensions=cc,cpp,cxx,h,hpp,hxx --headers=h,hpp,hxx --linelength=120 --quiet /home/vagrant/prcpp/workspace/uebungen/matrix/src/main.cpp && touch /home/vagrant/prcpp/workspace/cmake-build-release/uebungen/matrix/cpplint/src/main.cpp.timestamp

uebung_matrix_app-cpplint: uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint
uebung_matrix_app-cpplint: uebungen/matrix/cpplint/src/main.cpp.timestamp
uebung_matrix_app-cpplint: uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/build.make

.PHONY : uebung_matrix_app-cpplint

# Rule to build all files generated by this target.
uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/build: uebung_matrix_app-cpplint

.PHONY : uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/build

uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/clean:
	cd /home/vagrant/prcpp/workspace/cmake-build-release/uebungen/matrix && $(CMAKE_COMMAND) -P CMakeFiles/uebung_matrix_app-cpplint.dir/cmake_clean.cmake
.PHONY : uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/clean

uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/depend:
	cd /home/vagrant/prcpp/workspace/cmake-build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vagrant/prcpp/workspace /home/vagrant/prcpp/workspace/uebungen/matrix /home/vagrant/prcpp/workspace/cmake-build-release /home/vagrant/prcpp/workspace/cmake-build-release/uebungen/matrix /home/vagrant/prcpp/workspace/cmake-build-release/uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : uebungen/matrix/CMakeFiles/uebung_matrix_app-cpplint.dir/depend
