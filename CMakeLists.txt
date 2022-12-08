# CMake 3.8+ has build-in cuda support
cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(vsg-test LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

## VulkanSceneGraph
##################################################
find_package(vsg REQUIRED)

vsg_setup_dir_vars()
vsg_setup_build_vars()

vsg_add_target_clang_format(
    FILES
        ${PROJECT_SOURCE_DIR}/include/*/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*.cpp
)
vsg_add_target_cppcheck(
    FILES
        ${PROJECT_SOURCE_DIR}/include/*/*.h
        ${PROJECT_SOURCE_DIR}/src/*/*.cpp
)
vsg_add_target_clobber()
vsg_add_target_docs(
    FILES
        ${PROJECT_SOURCE_DIR}/include/*/*.h
)
vsg_add_target_uninstall()
##################################################


file(GLOB SOURCES "src/*.cpp")

add_executable(main ${SOURCES})