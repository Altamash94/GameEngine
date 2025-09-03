cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(GameEngine VERSION 0.1.0)

find_package(OpenGL REQUIRED)

# Define platform-specific variables
set(install_header_dir ${CMAKE_SOURCE_DIR}/build/install/include)
if(WIN32)
    set(glad_folder_name glad_windows)
    set(install_lib_dir ${CMAKE_SOURCE_DIR}/build/install/bin)
elseif(UNIX)
    set(glad_folder_name glad_unix)
    set(install_lib_dir ${CMAKE_SOURCE_DIR}/build/install/lib)
else()
    message(STATUS "Unknown platform")
    return()
endif()


set(my_include_dirs 
    ${CMAKE_SOURCE_DIR}/external 
    ${CMAKE_SOURCE_DIR}/external/${glad_folder_name}/include 
    ${CMAKE_SOURCE_DIR}/external/GLFW/glfw-3.4/include)

add_subdirectory(external)
add_subdirectory(source)

set(SOURCES source/main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/external/${glad_folder_name}/src/glad.c)

set(CMAKE_INSTALL_RPATH ${install_lib_dir})
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

add_executable(${PROJECT_NAME} ${SOURCES})
foreach(include_dir IN LISTS my_include_dirs)
    target_include_directories(${PROJECT_NAME} PRIVATE ${include_dir})
endforeach()
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE add glad glfw shader texture camera object cube debugline)

# Install the executable into bin/
install(TARGETS GameEngine
RUNTIME DESTINATION bin
)

# Install textures into bin/textures
install(DIRECTORY ${CMAKE_SOURCE_DIR}/source/textures/textures/
    DESTINATION bin/textures
    FILES_MATCHING PATTERN "*.*"
)
#Install shaders into bin/shaders
install(DIRECTORY ${CMAKE_SOURCE_DIR}/source/shader/shader/
    DESTINATION bin/shader
    FILES_MATCHING PATTERN "*.glsl"
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/glad/
    DESTINATION include
    FILES_MATCHING PATTERN "*.*"
)