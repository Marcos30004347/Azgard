cmake_minimum_required(VERSION 3.10)

add_executable(azgard_sandbox main.cpp)

target_link_libraries(azgard_sandbox PRIVATE azgard)