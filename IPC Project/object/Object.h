#ifndef OBJECT_H
#define OBJECT_H
#include <iostream>
#include <memory>
#include <vector>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "./../../shader/Shader.h"
#include "./../../textures/Texture.h"
class Object
{
public:
	Object();
	glm::mat4 model;
	virtual void Draw() const = 0;
	void SetModel(float angle, glm::vec3 axis, glm::vec3 position, glm::vec3 scale);
	~Object();
	void SetShader(const char* vertexShaderFile, const char* fragmentShaderFile);
	void SetShader(Shader* shader);
	void AddTexture(Texture* texture);
protected:
	virtual void InitializeBuffers(float* vertices, int size) = 0;
	unsigned int VBO, VAO;
	Shader* shader = nullptr;
	std::vector<Texture*> textures;
};
#endif // !OBJECT_H