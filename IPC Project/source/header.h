#pragma once
#include <iostream>
#include <unistd.h>
#define GLAD_GL_IMPLEMENTATION
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera/CameraDebug.h"
#include "shader/Shader.h"
#include "textures/Texture.h"
#include "object/cube/Cube.h"
#include "object/DebugLines/DebugLine.h"


const int WIDTH = 600, HEIGHT = 480;
double deltaTime = 0.0f;
double lastFrame = 0.0f;
GLFWwindow* window;
std::shared_ptr<Camera> camera;
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

int initializeGLFW();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

void CursorPositionCallback(GLFWwindow* window, double x, double y);