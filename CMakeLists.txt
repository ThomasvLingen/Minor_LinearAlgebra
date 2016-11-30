cmake_minimum_required(VERSION 3.6)
project(LinearAlgebra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(libs/imgui)

set(SOURCE_FILES
        src/main.cpp
        src/imgui_impl_sdl.cpp src/imgui_impl_sdl.h
        src/linal/LinalVector.cpp src/linal/LinalVector.hpp
        src/SDLImguiApplication.cpp src/SDLImguiApplication.hpp)

add_executable(LinearAlgebra ${SOURCE_FILES})