cmake_minimum_required(VERSION 3.18.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

PROJECT(GameEngine VERSION 0.1.0)

add_subdirectory(external)
add_subdirectory(source)
set(External_Directory ${CMAKE_CURRENT_SOURCE_DIR}/external)

find_package(OpenGL REQUIRED)

set(SOURCES source/main.cpp ${External_Directory}/glad/src/glad.c) 

set(CMAKE_INSTALL_RPATH ${CMAKE_CURRENT_SOURCE_DIR}/build/install/lib)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE add glad glfw shader texture camera object cube)

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
    DESTINATION ${CMAKE_SOURCE_DIR}/build/install/include
    FILES_MATCHING PATTERN "*.*"
)