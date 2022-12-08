# CMake 3.8+ has build-in cuda support
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(vsg-test LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})