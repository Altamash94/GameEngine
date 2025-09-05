cmake_minimum_required(VERSION 3.18.1)
project(object VERSION 0.0.1 DESCRIPTION "Object library")


add_library(${PROJECT_NAME} SHARED Object.cpp)
setup_rpath(${PROJECT_NAME})

#set includes and libs
foreach(include_dir IN LISTS my_include_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw shader texture)

#installs
install(TARGETS ${PROJECT_NAME} DESTINATION ${install_lib_dir})
install(FILES Object.h DESTINATION ${install_header_dir})


add_subdirectory(cube)
add_subdirectory(DebugLines)