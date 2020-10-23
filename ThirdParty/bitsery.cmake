add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/bitsery)

function(link_bitsery_on_target)
    message("Linking bitsery on target ${ARGV0}")

    target_link_libraries(${ARGV0} PRIVATE bitsery)
endfunction()