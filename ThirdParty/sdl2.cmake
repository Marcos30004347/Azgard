add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/SDL2)

set(SDL2_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/SDL2/include")
set(SDL2_LIBRARIES "SDL2-static")

function(link_sdl2_on_target)
    message("Linking SDL2 on target ${ARGV0}")
    target_link_libraries(${ARGV0} PRIVATE ${SDL2_LIBRARIES})
    target_include_directories(${ARGV0} PUBLIC ${SDL2_INCLUDE_DIRS})
endfunction()