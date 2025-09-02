cmake_minimum_required(VERSION 3.18.1)
project(MyAddLibrary VERSION 0.0.1 DESCRIPTION "Object library")

set(External_Directory ${CMAKE_SOURCE_DIR}/external)
set(GladSrc ${External_Directory}/glad/src/gl.c)

add_library(object SHARED Object.cpp)
target_include_directories(object PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include/object)

install(TARGETS object DESTINATION ${LIBDIR})
install(FILES Object.h DESTINATION ${HEADERDIR} )

add_subdirectory(cube)