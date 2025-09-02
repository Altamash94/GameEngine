#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera/CameraDebug.h"
#include "shader/Shader.h"
#include "textures/Texture.h"
#include "object/cube/Cube.h"



int initializeGLFW();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
const int WIDTH = 600, HEIGHT = 480;
double deltaTime = 0.0f;
double lastFrame = 0.0f;

GLFWwindow* window;
Camera* camera = nullptr;

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

void PreDrawCheckErrors();
void PostDrawCheckErrors();

void processInput(GLFWwindow* window)
{
    double cameraSpeed = 2.5f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::FRONT, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::BACK, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::LEFT, cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->Move(Camera::MoveDirection::RIGHT, cameraSpeed);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void CursorPositionCallback(GLFWwindow* window, double x, double y);

void PreDrawCheckErrors()
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "GL error pre-draw: " << std::hex << err << std::dec << std::endl;
    }

    const char* msg = "Before drawing line";
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
                         GL_DEBUG_SEVERITY_NOTIFICATION, (GLsizei)strlen(msg), msg);
}


void PostDrawCheckErrors() 
{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "GL error post-draw: " << std::hex << err << std::dec << std::endl;
    }

    const char* msg = "After drawing line";
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 2,
                         GL_DEBUG_SEVERITY_NOTIFICATION, (GLsizei)strlen(msg), msg);
}




//Debug