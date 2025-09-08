cmake_minimum_required(VERSION 3.10)
project(RANDX)

set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O2 -s")

add_library(randx STATIC randx.c)
target_include_directories(randx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
