function(link_opengl_on_target)
    message("Linking OpenGL on target ${ARGV0}")

    set(OpenGL_GL_PREFERENCE "GLVND")
    find_package(OpenGL REQUIRED)

    target_link_libraries(${ARGV0} PRIVATE ${OPENGL_LIBRARIES})
    target_include_directories(${ARGV0} PRIVATE ${OPENGL_INCLUDE_DIRS})
endfunction()