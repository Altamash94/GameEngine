cmake_minimum_required(VERSION 3.18.1)
project(glad VERSION 0.0.1 DESCRIPTION "Glad header")

set(External_Directory ${CMAKE_SOURCE_DIR}/external)
set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include/glad)

add_library(glad SHARED src/glad.c)
target_include_directories(glad PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS glad DESTINATION ${LIBDIR})
install(FILES include/glad/glad.h DESTINATION ${HEADERDIR})
install(FILES include/KHR/khrplatform.h DESTINATION ${HEADERDIR})