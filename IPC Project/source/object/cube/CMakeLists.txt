cmake_minimum_required(VERSION 3.18.1)
project(CubeLibrary VERSION 0.0.1 DESCRIPTION "Cube library for creation of cube")

add_library(cube SHARED Cube.cpp)
target_include_directories(cube PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include)

install(TARGETS cube DESTINATION ${LIBDIR})
install(FILES Cube.h DESTINATION ${HEADERDIR} )