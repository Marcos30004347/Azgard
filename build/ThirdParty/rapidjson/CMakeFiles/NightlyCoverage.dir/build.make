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

# Utility rule file for NightlyCoverage.

# Include the progress variables for this target.
include ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/progress.make

ThirdParty/rapidjson/CMakeFiles/NightlyCoverage:
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson && /snap/cmake/619/bin/ctest -D NightlyCoverage

NightlyCoverage: ThirdParty/rapidjson/CMakeFiles/NightlyCoverage
NightlyCoverage: ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/build.make

.PHONY : NightlyCoverage

# Rule to build all files generated by this target.
ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/build: NightlyCoverage

.PHONY : ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/build

ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/clean:
	cd /home/marcos/workspace/azgard/build/ThirdParty/rapidjson && $(CMAKE_COMMAND) -P CMakeFiles/NightlyCoverage.dir/cmake_clean.cmake
.PHONY : ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/clean

ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/depend:
	cd /home/marcos/workspace/azgard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/workspace/azgard /home/marcos/workspace/azgard/ThirdParty/rapidjson /home/marcos/workspace/azgard/build /home/marcos/workspace/azgard/build/ThirdParty/rapidjson /home/marcos/workspace/azgard/build/ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ThirdParty/rapidjson/CMakeFiles/NightlyCoverage.dir/depend

