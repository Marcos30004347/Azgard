add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/crc)

function(link_crc_on_target)
    message("Linking crc on target ${ARGV0}")
    target_link_libraries(${ARGV0} PRIVATE crc)
endfunction()