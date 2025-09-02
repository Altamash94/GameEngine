cmake_minimum_required(VERSION 3.18.1)
project(MyAddLibrary VERSION 0.0.1 DESCRIPTION "Add library for testing")

add_library(add SHARED Add.cpp)
set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include)

install(TARGETS add DESTINATION ${LIBDIR})
install(FILES Add.h DESTINATION ${HEADERDIR} )