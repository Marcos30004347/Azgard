add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/jobin)

function(link_jobin_on_target)
    message("Linking jobin on target ${ARGV0}")

    target_link_libraries(${ARGV0} PRIVATE jobin)
endfunction()