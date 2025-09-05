cmake_minimum_required(VERSION 3.18.1)
project(texture VERSION 0.0.1 DESCRIPTION "texture library")

add_library(texture SHARED Texture.cpp)
setup_rpath(${PROJECT_NAME})

#set includes and libs
foreach(include_dir IN LISTS my_include_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

#installs
install(TARGETS ${PROJECT_NAME} DESTINATION ${install_lib_dir})
install(FILES Texture.h DESTINATION ${install_header_dir})