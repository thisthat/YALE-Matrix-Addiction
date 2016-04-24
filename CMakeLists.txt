cmake_minimum_required(VERSION 3.5)
project(project_1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp
    Main.hpp
    Makefile
    YSMF.cpp
    YSMF.hpp
        Mul.cpp Mul.hpp)

add_executable(project_1 ${SOURCE_FILES})