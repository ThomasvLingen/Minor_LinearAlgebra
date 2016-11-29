cmake_minimum_required(VERSION 3.6)
project(LinearAlgebra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(libs/imgui)

set(SOURCE_FILES
        src/imgui_impl_sdl.h
        src/imgui_impl_sdl.cpp
        src/main.cpp)

add_executable(LinearAlgebra ${SOURCE_FILES})