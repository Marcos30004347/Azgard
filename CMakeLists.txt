cmake_minimum_required(VERSION 3.10)

include(cmake/set_target_option.cmake)

project(azgard)

#Azgard compile options

# If set, azgard will be compiled as debug build
option(AZGARD_DEBUG_BUILD "Azgard debug mode" ON)

# If set, azgard will use the standart c math library as backend for the math library
option(AZGARD_USE_STANDART_MATH "Azgard should use standart c math library" ON)

# If set, azgard will be compiled as a shared library.
option(AZGARD_SHARED_LIB_BUILD "Azgard should be compiled as a shared library" OFF)


if(AZGARD_DEBUG_BUILD)
  # add_compile_options( "-Wall" "-Wpedantic" "-Wextra" "-fexceptions $<$<CONFIG:DEBUG>:-O0;-g3;-ggdb>")
endif()

# Include dependencies cmake
include(ThirdParty/glew.cmake)
include(ThirdParty/sdl2.cmake)
include(ThirdParty/opengl.cmake)
include(ThirdParty/bitsery.cmake)
include(ThirdParty/crc.cmake)
include(ThirdParty/rapidjson.cmake)
include(ThirdParty/rapidxml.cmake)
include(ThirdParty/tracy.cmake)

# Set output directories (some dependencie can change those variables)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "")

# Copy asset files
file(COPY Engine/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Set azgard lib type
if(AZGARD_SHARED_LIB_BUILD)
  set(AZGARD_LIB_TYPE SHARED)
else()
  set(AZGARD_LIB_TYPE STATIC)
endif()

# Compile library
add_library(azgard ${AZGARD_LIB_TYPE}
#Core
Engine/Core/Assert.cpp
Engine/Core/Math.cpp

#Runtime
Engine/Runtime/Engine.cpp

#Debug
Engine/Debug/Debugger.cpp
Engine/Debug/Logger.cpp

#Library
Engine/Library/SpinLock.cpp
Engine/Library/Window.cpp
Engine/Library/StringId.cpp
Engine/Library/String.cpp
Engine/Library/File.cpp
Engine/Library/Time.cpp
Engine/Library/Thread.cpp

#File Formats
Engine/Format/Xml.cpp
Engine/Format/Json.cpp

#Memory
Engine/Memory/Memory.cpp
Engine/Memory/MemoryPool.cpp
Engine/Memory/MemoryManager.cpp
)

# Public include directories
target_include_directories(azgard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

# Set azgard compile definitions(options)
set_target_option(azgard AZGARD_DEBUG_BUILD)
set_target_option(azgard AZGARD_USE_STANDART_MATH)
set_target_option(azgard AZGARD_SHARED_LIB_BUILD)

# Link Third Party dependencies
link_glew_on_target(azgard)
link_opengl_on_target(azgard)
link_sdl2_on_target(azgard)
link_bitsery_on_target(azgard)
link_crc_on_target(azgard)
link_rapidjson_on_target(azgard)
link_rapidxml_on_target(azgard)
link_tracy_on_target(azgard)


add_subdirectory(Sandbox)