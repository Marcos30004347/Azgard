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

if(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")

set(USE_FLAGS "${USE_FLAGS} -o3")
set(USE_FLAGS "${USE_FLAGS} -std=c++17")
set(USE_FLAGS "${USE_FLAGS} -s WASM=1")
set(USE_FLAGS "${USE_FLAGS} -s ASYNCIFY=1")
set(USE_FLAGS "${USE_FLAGS} -s USE_PTHREADS=1")
set(USE_FLAGS "${USE_FLAGS} -s PTHREAD_POOL_SIZE=8")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
set(CMAKE_EXECUTABLE_SUFFIX .js)

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
include(ThirdParty/stb.cmake)
include(ThirdParty/cross-fiber.cmake)
include(ThirdParty/fcontext.cmake)

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
Engine/Core/SpinLock.cpp
Engine/Core/Window.cpp
Engine/Core/Thread.cpp

#Runtime
Engine/Runtime/Engine.cpp
Engine/Runtime/TimeManager.cpp

#Debug
Engine/Debug/Debugger.cpp
Engine/Debug/Logger.cpp

#Library
Engine/Library/Name.cpp
Engine/Library/String.cpp
Engine/Library/LibraryManager.cpp

#File
Engine/File/FileManager.cpp
Engine/File/FileHandle.cpp

#File Formats
Engine/Format/Xml.cpp
Engine/Format/Json.cpp

#Memory
Engine/Memory/Memory.cpp
Engine/Memory/MemoryPool.cpp
Engine/Memory/MemoryManager.cpp

#Event
Engine/Event/EventManager.cpp

#Job
Engine/Job/Fiber.cpp

#Renderer
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
link_stb_headers_on_target(azgard)
link_fcontext_on_target(azgard)
link_cross_fiber_on_target(azgard)



add_subdirectory(Sandbox)