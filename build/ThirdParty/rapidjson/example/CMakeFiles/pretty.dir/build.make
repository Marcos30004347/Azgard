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
include ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/depend.make

# Include the progress variables for this target.
include ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/progress.make

# Include the compile flags for this target's objects.
include ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/flags.make

ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.o: ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/flags.make
ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.o: ../ThirdParty/rapidjson/example/pretty/pretty.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.o"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pretty.dir/pretty/pretty.cpp.o -c /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/pretty/pretty.cpp

ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pretty.dir/pretty/pretty.cpp.i"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/pretty/pretty.cpp > CMakeFiles/pretty.dir/pretty/pretty.cpp.i

ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pretty.dir/pretty/pretty.cpp.s"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/workspace/azgard/ThirdParty/rapidjson/example/pretty/pretty.cpp -o CMakeFiles/pretty.dir/pretty/pretty.cpp.s

# Object files for target pretty
pretty_OBJECTS = \
"CMakeFiles/pretty.dir/pretty/pretty.cpp.o"

# External object files for target pretty
pretty_EXTERNAL_OBJECTS =

bin/pretty: ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/pretty/pretty.cpp.o
bin/pretty: ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/build.make
bin/pretty: ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/pretty"
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pretty.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/build: bin/pretty

.PHONY : ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/build

ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/clean:
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example && $(CMAKE_COMMAND) -P CMakeFiles/pretty.dir/cmake_clean.cmake
.PHONY : ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/clean

ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/depend:
	cd /home/marcos/workspace/azgard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/workspace/azgard /home/marcos/workspace/azgard/ThirdParty/rapidjson/example /home/marcos/workspace/azgard/build /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/rapidjson/example/CMakeFiles/pretty.dir/depend

