cmake_minimum_required(VERSION 3.10)

project(crc)

add_library(crc STATIC
crc/crc16.c
crc/crc32.c
crc/crc64.c
crc/crchash.cpp
)

target_include_directories(
    crc
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/crc
)
