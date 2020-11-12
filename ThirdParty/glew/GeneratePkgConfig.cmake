function(GeneratePkgConfigFile target description)
    cmake_parse_arguments(pc "" "NAME;REQUIRES;LIBRARY_DIR" "" ${ARGV})
    if(NOT pc_LIBRARY_DIR)
        set(pc_LIBRARY_DIR ${CMAKE_INSTALL_LIBDIR})
    endif()
    if(WIN32)
        set(PKGCONFIG_INSTALL_DIR)
    else()
        set(PKGCONFIG_INSTALL_DIR ${pc_LIBRARY_DIR}/pkgconfig)
    endif()
    if(NOT pc_NAME)
        set(pc_NAME ${target})
    endif()

    get_property(raw_definitions TARGET ${target} PROPERTY INTERFACE_COMPILE_DEFINITIONS)
    set(definitions "")
    foreach(def IN LISTS raw_definitions)
        if(def MATCHES "-D")
            list(APPEND definitions ${def})
        else()
            list(APPEND definitions "-D${def}")
        endif()
    endforeach()
    list(JOIN definitions " " definitions)

    get_property(target_output TARGET ${target} PROPERTY OUTPUT_NAME)
    get_filename_component(target_output ${target_output} NAME)
    set(links "-l${target_output}")
    get_property(raw_links TARGET ${target} PROPERTY INTERFACE_LINK_LIBRARIES)
    foreach(link IN LISTS raw_links)
        if(link MATCHES "-l")
            list(APPEND links ${link})
        elseif(TARGET ${link})
            get_property(link_target TARGET ${link} PROPERTY OUTPUT_NAME)
            list(APPEND links ${link_target})
        else()
            list(APPEND links "-l${link}")
        endif()
    endforeach()
    list(JOIN links " " links)
    get_property(version TARGET ${target} PROPERTY VERSION)

    set(out_file "${CMAKE_CURRENT_BINARY_DIR}/${pc_NAME}.pc")
    file(WRITE ${out_file} "prefix=${CMAKE_INSTALL_PREFIX}\n")
    file(APPEND ${out_file} "exec_prefix=\${prefix}\n")
    file(APPEND ${out_file} "libdir=\${prefix}/${pc_LIBRARY_DIR}\n")
    file(APPEND ${out_file} "includedir=\${prefix}/include\n")
    file(APPEND ${out_file} "\n")
    file(APPEND ${out_file} "Name: ${pc_NAME}\n")
    file(APPEND ${out_file} "Description: ${description}\n")
    file(APPEND ${out_file} "Version: ${version}\n")
    file(APPEND ${out_file} "Cflags: -I\${includedir} ${definitions}\n")
    file(APPEND ${out_file} "Libs: -L\${libdir} ${links}\n")
    if(pc_REQUIRES)
        file(APPEND ${out_file} "Requires: ${pc_REQUIRES}")
    endif()
    install(FILES ${out_file} DESTINATION "${PKGCONFIG_INSTALL_DIR}")
endfunction()