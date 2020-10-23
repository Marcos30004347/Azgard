set(CMAKE_CXX_STANDARD 11)

option(TRACY_ENABLE "Profiling is enabled" OFF)
option(TRACY_ON_DEMAND "Profiling enabled on demand" ON)
option(TRACY_NO_EXIT "Client executable does not exit until all profile data is sent to server" OFF)
option(TRACY_NO_BROADCAST "Disable client discovery by broadcast to local network" OFF)
option(TRACY_NO_CODE_TRANSFER "Disable client code transfer over network" OFF)

add_library(tracy_client ./ThirdParty/tracy/TracyClient.cpp)

# add_definitions(-DNDEBUG)

macro(set_option OPTION)
if(${OPTION})
message(STATUS "${OPTION}: ON")
target_compile_definitions(tracy_client PUBLIC ${OPTION})
else()
message(STATUS "${OPTION}: OFF")
endif()
endmacro()

if(AZG_DEBUG_BUILD)
set(TRACY_ENABLE OPTION ON)
endif()

set_option(TRACY_ENABLE)
set_option(TRACY_ON_DEMAND)
set_option(TRACY_NO_EXIT)
set_option(TRACY_NO_BROADCAST)
set_option(TRACY_NO_CODE_TRANSFER)

if(NOT AZG_DEBUG_PORT)
set(TRACY_PORT 8086)
endif()

message(STATUS "TRACY_PORT: ${TRACY_PORT}")

find_library(DL_LIBRARY_PATH dl)

target_compile_definitions(tracy_client PUBLIC TRACY_PORT=${TRACY_PORT})

target_include_directories(tracy_client PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_link_libraries(tracy_client PRIVATE ${DL_LIBRARY_PATH})

function(link_tracy_on_target)
    message("Linking tracy on target ${ARGV0}")
    target_link_libraries(${ARGV0} PUBLIC tracy_client)
endfunction()