cmake_minimum_required (VERSION 3.15)

project(example)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_subdirectory("./log")
add_subdirectory("./ReadAppList")
add_subdirectory("./window")
