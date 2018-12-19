cmake_minimum_required(VERSION 3.13)
project(Chimeric)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Chimeric)

include_directories(Chimeric)
add_subdirectory(Test)