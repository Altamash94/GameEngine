cmake_minimum_required(VERSION 3.18.1)
project(glad VERSION 0.0.1 DESCRIPTION "Glad header")

add_library(glad SHARED src/glad.c)

#set includes and libs
foreach(include_dir IN LISTS my_include_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
endforeach()

#installs
install(TARGETS ${PROJECT_NAME} DESTINATION ${install_lib_dir})
install(FILES include/glad/glad.h DESTINATION ${install_header_dir})
install(FILES include/KHR/khrplatform.h DESTINATION ${install_header_dir})