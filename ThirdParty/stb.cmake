function(link_stb_headers_on_target)
    message("Linking STB headers on target ${ARGV0}")
    target_include_directories(${ARGV0} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/stb)
endfunction()