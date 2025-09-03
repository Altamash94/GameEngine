cmake_minimum_required(VERSION 3.18.1)
project(cube VERSION 0.0.1 DESCRIPTION "Cube library for creation of cube")

add_library(cube SHARED Cube.cpp)
foreach(include_dir IN LISTS my_include_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE shader)
target_link_libraries(${PROJECT_NAME} PRIVATE object)

#installs
install(TARGETS ${PROJECT_NAME} DESTINATION ${install_lib_dir})
install(FILES Cube.h DESTINATION ${install_header_dir})