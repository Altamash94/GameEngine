#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <memory>
#include <vector>
#include <unistd.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "./../shader/Shader.h"
#include "./../textures/Texture.h"
#include "./../Camera/Camera.h"

#ifndef SHADER_DIR
    #if defined(_WIN32)
        #define SHADER_DIR "D:\\Projects\\GameEngine\\GameEngine\\IPC Project\\build\\install\\bin\\shader\\"
    #elif defined(__linux__)
        #define SHADER_DIR "/home/altamash/Documents/temp/GE/GameEngine/IPC Project/build/install/bin/shader/"
    #else
        #error "Unknown platform. Please define SHADER_DIR manually."
    #endif
#endif


enum SPACE{WORLD_SPACE = 0, VIEW_SPACE = 1, CAMERA_SPACE = 2};

class Object
{
public:
	Object(const char* vertexShaderFile, const char* fragmentShaderFile);
	virtual ~Object();
	glm::mat4 model;
	virtual void Draw() const = 0;
	void SetModel(float angle, glm::vec3 axis, glm::vec3 position, glm::vec3 scale);
	void SetCamera(std::shared_ptr<Camera> camera);
	void AddTexture(const char* texturePath, const char* uniformName, int id);
	SPACE space = WORLD_SPACE;
protected:
	virtual void InitializeBuffers(float* vertices, int size) = 0;
	unsigned int VBO, VAO;
	std::shared_ptr<Camera> camera;
	std::unique_ptr<Shader> shader;
	std::vector<std::unique_ptr<Texture>> textures;
	void PreDrawCheckErrors() const;
	void PostDrawCheckErrors() const;
};
#endif // !OBJECT_H