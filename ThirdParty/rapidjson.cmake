add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/rapidjson)

function(link_rapidjson_on_target)
    message("Linking rapidjson on target ${ARGV0}")
    target_include_directories(${ARGV0} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ThirdParty/rapidjson/include)
endfunction()