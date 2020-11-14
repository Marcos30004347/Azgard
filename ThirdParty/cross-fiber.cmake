add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/cross-fiber)

function(link_cross_fiber_on_target)
    message("Linking cross-fiber on target ${ARGV0}")
    target_link_libraries(${ARGV0} PUBLIC cross-fiber)
endfunction()