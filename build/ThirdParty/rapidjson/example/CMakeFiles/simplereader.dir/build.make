# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /snap/cmake/619/bin/cmake

# The command to remove a file.
RM = /snap/cmake/619/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/marcos/workspace/azgard

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/marcos/workspace/azgard/build

# Include any dependencies generated for this target.
include ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/flags.make

ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o: ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/flags.make
ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o: ../ThirdParty/rapidjson/example/simplereader/simplereader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o -c /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/simplereader/simplereader.cpp

ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/simplereader/simplereader.cpp > CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.i

ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/simplereader/simplereader.cpp -o CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.s

# Object files for target simplereader
simplereader_OBJECTS = \
"CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o"

# External object files for target simplereader
simplereader_EXTERNAL_OBJECTS =

bin/simplereader: ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/simplereader/simplereader.cpp.o
bin/simplereader: ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/build.make
bin/simplereader: ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/simplereader"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/simplereader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/build: bin/simplereader

.PHONY : ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/build

ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/clean:
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && $(CMAKE_COMMAND) -P CMakeFiles/simplereader.dir/cmake_clean.cmake
.PHONY : ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/clean

ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/depend:
	cd /home/marcos/workspace/azgard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/workspace/azgard /home/marcos/workspace/azgard/ThirdParty/rapidjson/example /home/marcos/workspace/azgard/build /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/rapidjson/example/CMakeFiles/simplereader.dir/depend

