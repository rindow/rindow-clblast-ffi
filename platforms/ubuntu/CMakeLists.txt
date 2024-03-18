cmake_minimum_required(VERSION 3.14)

#enable_testing()

project(rindow-clblast-ubuntu VERSION 1.0.0 LANGUAGES CXX C)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE srcfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ./*.cpp)
add_library(rindowclblast SHARED ${srcfiles})
