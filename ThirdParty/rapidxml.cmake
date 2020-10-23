function(link_rapidxml_on_target)
    message("Linking rapidxml on target ${ARGV0}")
    target_include_directories(${ARGV0} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/rapidxml)
endfunction()