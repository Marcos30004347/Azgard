function(set_target_option)
if(${ARGV1})
message(STATUS "${ARGV1}: ON")
target_compile_definitions(${ARGV0} PUBLIC ${ARGV1})
else()
message(STATUS "${ARGV1}: OFF")
endif()
endfunction()