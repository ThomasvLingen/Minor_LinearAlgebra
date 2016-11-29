cmake_minimum_required(VERSION 3.6)
project(LinearAlgebra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(libs/imgui)
include_directories(libs/GL/include)

set(SOURCE_FILES
    src/imgui_impl_sdl_gl3.cpp
    src/imgui_impl_sdl_gl3.h
    src/main.cpp)

add_executable(LinearAlgebra ${SOURCE_FILES})