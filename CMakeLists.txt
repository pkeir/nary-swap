cmake_minimum_required(VERSION 3.6)

set(n nary-swap)
project(${n})
add_executable(${n} swap.cpp)
#set_target_properties(${n} PROPERTIES CXX_STANDARD 17) # newer CMake
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
target_compile_options(${n} PRIVATE -Wall -Wno-unused-value)

