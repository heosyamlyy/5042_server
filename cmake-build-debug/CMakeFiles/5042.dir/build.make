# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuyang016/CLionProjects/5042

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuyang016/CLionProjects/5042/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/5042.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/5042.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/5042.dir/flags.make

CMakeFiles/5042.dir/main.cpp.o: CMakeFiles/5042.dir/flags.make
CMakeFiles/5042.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/5042.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5042.dir/main.cpp.o -c /Users/liuyang016/CLionProjects/5042/main.cpp

CMakeFiles/5042.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5042.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuyang016/CLionProjects/5042/main.cpp > CMakeFiles/5042.dir/main.cpp.i

CMakeFiles/5042.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5042.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuyang016/CLionProjects/5042/main.cpp -o CMakeFiles/5042.dir/main.cpp.s

CMakeFiles/5042.dir/connection.cpp.o: CMakeFiles/5042.dir/flags.make
CMakeFiles/5042.dir/connection.cpp.o: ../connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/5042.dir/connection.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5042.dir/connection.cpp.o -c /Users/liuyang016/CLionProjects/5042/connection.cpp

CMakeFiles/5042.dir/connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5042.dir/connection.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuyang016/CLionProjects/5042/connection.cpp > CMakeFiles/5042.dir/connection.cpp.i

CMakeFiles/5042.dir/connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5042.dir/connection.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuyang016/CLionProjects/5042/connection.cpp -o CMakeFiles/5042.dir/connection.cpp.s

CMakeFiles/5042.dir/game.cpp.o: CMakeFiles/5042.dir/flags.make
CMakeFiles/5042.dir/game.cpp.o: ../game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/5042.dir/game.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5042.dir/game.cpp.o -c /Users/liuyang016/CLionProjects/5042/game.cpp

CMakeFiles/5042.dir/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5042.dir/game.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuyang016/CLionProjects/5042/game.cpp > CMakeFiles/5042.dir/game.cpp.i

CMakeFiles/5042.dir/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5042.dir/game.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuyang016/CLionProjects/5042/game.cpp -o CMakeFiles/5042.dir/game.cpp.s

CMakeFiles/5042.dir/server.cpp.o: CMakeFiles/5042.dir/flags.make
CMakeFiles/5042.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/5042.dir/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/5042.dir/server.cpp.o -c /Users/liuyang016/CLionProjects/5042/server.cpp

CMakeFiles/5042.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/5042.dir/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/liuyang016/CLionProjects/5042/server.cpp > CMakeFiles/5042.dir/server.cpp.i

CMakeFiles/5042.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/5042.dir/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/liuyang016/CLionProjects/5042/server.cpp -o CMakeFiles/5042.dir/server.cpp.s

# Object files for target 5042
5042_OBJECTS = \
"CMakeFiles/5042.dir/main.cpp.o" \
"CMakeFiles/5042.dir/connection.cpp.o" \
"CMakeFiles/5042.dir/game.cpp.o" \
"CMakeFiles/5042.dir/server.cpp.o"

# External object files for target 5042
5042_EXTERNAL_OBJECTS =

5042: CMakeFiles/5042.dir/main.cpp.o
5042: CMakeFiles/5042.dir/connection.cpp.o
5042: CMakeFiles/5042.dir/game.cpp.o
5042: CMakeFiles/5042.dir/server.cpp.o
5042: CMakeFiles/5042.dir/build.make
5042: CMakeFiles/5042.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable 5042"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/5042.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/5042.dir/build: 5042

.PHONY : CMakeFiles/5042.dir/build

CMakeFiles/5042.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/5042.dir/cmake_clean.cmake
.PHONY : CMakeFiles/5042.dir/clean

CMakeFiles/5042.dir/depend:
	cd /Users/liuyang016/CLionProjects/5042/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuyang016/CLionProjects/5042 /Users/liuyang016/CLionProjects/5042 /Users/liuyang016/CLionProjects/5042/cmake-build-debug /Users/liuyang016/CLionProjects/5042/cmake-build-debug /Users/liuyang016/CLionProjects/5042/cmake-build-debug/CMakeFiles/5042.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/5042.dir/depend

