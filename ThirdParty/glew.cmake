add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glew)

function(link_glew_on_target)
    message("Linking glew on target ${ARGV0}")

    target_link_libraries(${ARGV0} PUBLIC libglew_static)
endfunction()