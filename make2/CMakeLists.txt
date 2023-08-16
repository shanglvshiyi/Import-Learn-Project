cmake_minimum_required(VERSION 3.0)

project(SWAP)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

set(CMAKE_BUILD_TYPE Debug)

include_directories(include)

add_executable(swap_exe main.cpp src/swap.cpp)