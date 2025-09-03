if(WIN32)
    message(STATUS "Building on Windows")
    add_subdirectory(glad_windows)
elseif(UNIX)
    message(STATUS "Building on Linux/Unix")
    add_subdirectory(glad_unix)
else()
    message(STATUS "Unknown platform")
endif()


add_subdirectory(GLFW)
add_subdirectory(glm)