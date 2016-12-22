cmake_minimum_required(VERSION 3.5)
project(ecma-c)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ast.h ast.cpp)
add_executable(ecma-c ${SOURCE_FILES})