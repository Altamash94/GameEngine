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
#define SHADER_DIR "D:\\Projects\\GameEngine\\GameEngine\\IPC Project\\build\\install\\bin\\shader\\"
#endif

enum SPACE{WORLD_SPACE = 0, VIEW_SPACE = 1, CAMERA_SPACE = 2};

class Object
{
public:
	Object();
	glm::mat4 model;
	virtual void Draw() const = 0;
	void SetModel(float angle, glm::vec3 axis, glm::vec3 position, glm::vec3 scale);
	virtual ~Object();
	void SetShader(const char* vertexShaderFile, const char* fragmentShaderFile);
	void SetShader(Shader* shader);
	void AddTexture(Texture* texture);
	void SetCamera(Camera* camera) { this->camera = camera; }
	SPACE space = WORLD_SPACE;
protected:
	virtual void InitializeBuffers(float* vertices, int size) = 0;
	unsigned int VBO, VAO;
	Camera *camera = nullptr;
	Shader* shader = nullptr;
	std::vector<Texture*> textures;
	
};
#endif // !OBJECT_H