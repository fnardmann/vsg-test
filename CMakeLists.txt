cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(vsg-test LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

find_package(vsg REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(main ${SOURCES})

target_link_libraries(main vsg::vsg)
