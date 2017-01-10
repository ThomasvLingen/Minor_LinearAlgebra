cmake_minimum_required(VERSION 3.6)
project(LinearAlgebra)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(libs/imgui)

file(GLOB_RECURSE SOURCE_FILES
        "src/*.hpp"
        "src/*.cpp"
        "src/*.h"
        "src/*.tpp"
        )

add_executable(LinearAlgebra ${SOURCE_FILES})