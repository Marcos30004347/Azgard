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
include CMakeFiles/tracy_client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tracy_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tracy_client.dir/flags.make

CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o: CMakeFiles/tracy_client.dir/flags.make
CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o: ../ThirdParty/tracy/TracyClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o -c /home/marcos/workspace/azgard/ThirdParty/tracy/TracyClient.cpp

CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/marcos/workspace/azgard/ThirdParty/tracy/TracyClient.cpp > CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.i

CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/marcos/workspace/azgard/ThirdParty/tracy/TracyClient.cpp -o CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.s

# Object files for target tracy_client
tracy_client_OBJECTS = \
"CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o"

# External object files for target tracy_client
tracy_client_EXTERNAL_OBJECTS =

libtracy_client.a: CMakeFiles/tracy_client.dir/ThirdParty/tracy/TracyClient.cpp.o
libtracy_client.a: CMakeFiles/tracy_client.dir/build.make
libtracy_client.a: CMakeFiles/tracy_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/marcos/workspace/azgard/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtracy_client.a"
	$(CMAKE_COMMAND) -P CMakeFiles/tracy_client.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tracy_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tracy_client.dir/build: libtracy_client.a

.PHONY : CMakeFiles/tracy_client.dir/build

CMakeFiles/tracy_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tracy_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tracy_client.dir/clean

CMakeFiles/tracy_client.dir/depend:
	cd /home/marcos/workspace/azgard/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/marcos/workspace/azgard /home/marcos/workspace/azgard /home/marcos/workspace/azgard/build /home/marcos/workspace/azgard/build /home/marcos/workspace/azgard/build/CMakeFiles/tracy_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tracy_client.dir/depend

