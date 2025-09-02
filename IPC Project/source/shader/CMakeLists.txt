cmake_minimum_required(VERSION 3.18.1)
project(MyCameraLibrary VERSION 0.0.1 DESCRIPTION "Shader library")

set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include/Shader)

add_library(shader SHARED Shader.cpp)
target_include_directories(shader PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)

install(TARGETS shader DESTINATION ${LIBDIR})
install(FILES Shader.h DESTINATION ${HEADERDIR})