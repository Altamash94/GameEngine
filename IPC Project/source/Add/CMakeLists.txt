cmake_minimum_required(VERSION 3.18.1)
project(add VERSION 0.0.1 DESCRIPTION "Add library for testing")

add_library(add SHARED Add.cpp)

#installs
install(TARGETS ${PROJECT_NAME} DESTINATION ${install_lib_dir})
install(FILES Add.h DESTINATION ${install_header_dir})
