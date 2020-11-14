add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/fcontext)

function(link_fcontext_on_target)
    message("Linking fcontext on target ${ARGV0}")
    target_link_libraries(${ARGV0} PUBLIC fcontext)
endfunction()