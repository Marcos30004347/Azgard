cmake_minimum_required(VERSION 3.10)

project(azgard)

add_definitions(-DAZG_DEBUG_BUILD)

option(AZG_DEBUG_BUILD "Azgard debug mode" ON)

include(ThirdParty/glew.cmake)
include(ThirdParty/sdl2.cmake)
include(ThirdParty/opengl.cmake)
include(ThirdParty/jobin.cmake)
include(ThirdParty/bitsery.cmake)
include(ThirdParty/crc.cmake)
include(ThirdParty/rapidjson.cmake)
include(ThirdParty/rapidxml.cmake)
include(ThirdParty/tracy.cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "")
set(CMAKE_PDB_OUTPUT_DIRECTORY     "")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "")

# Copy asset files
file(COPY Engine/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(azgard STATIC
#Core
Engine/Core/Assert.cpp
Engine/Core/Math.cpp

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
)

if(AZG_DEBUG_BUILD)
message(STATUS "AZG_DEBUG_BUILD: ON")
target_compile_definitions(azgard PUBLIC AZG_DEBUG_BUILD)
endif()

target_include_directories(azgard PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Engine)

# Link Third Party dependencies
link_glew_on_target(azgard)
link_opengl_on_target(azgard)
link_sdl2_on_target(azgard)
link_jobin_on_target(azgard)
link_bitsery_on_target(azgard)
link_crc_on_target(azgard)
link_rapidjson_on_target(azgard)
link_rapidxml_on_target(azgard)
link_tracy_on_target(azgard)

add_subdirectory(Sandbox)