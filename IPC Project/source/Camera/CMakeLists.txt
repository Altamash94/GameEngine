cmake_minimum_required(VERSION 3.18.1)
project(MyCameraLibrary VERSION 0.0.1 DESCRIPTION "Library to handle camera")

set(External_Directory ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(LIBDIR ${CMAKE_SOURCE_DIR}/build/install/lib)
set(HEADERDIR ${CMAKE_SOURCE_DIR}/build/install/include/Camera)

set(CMAKE_INSTALL_RPATH ${CMAKE_SOURCE_DIR}/build/install/lib)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
add_library(camera SHARED Camera.cpp CameraDebug.cpp)
target_include_directories(camera PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
target_link_libraries(camera shader)
install(TARGETS camera DESTINATION ${LIBDIR})
install(FILES Camera.h CameraDebug.h DESTINATION ${HEADERDIR})