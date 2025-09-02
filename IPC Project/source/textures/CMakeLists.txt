cmake_minimum_required(VERSION 3.18.1)
project(MyCameraLibrary VERSION 0.0.1 DESCRIPTION "texture library")

set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include/Texture)

add_library(texture SHARED Texture.cpp)
target_include_directories(texture PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)

install(TARGETS texture DESTINATION ${LIBDIR})
install(FILES Texture.h DESTINATION ${HEADERDIR})