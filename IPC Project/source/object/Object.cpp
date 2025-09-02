#include "Object.h"

Object::Object()
{
	model = glm::mat4(1.0f);
	VAO = -1;
	VBO = -1;
}

Object::~Object()
{
    	glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
}

void Object::SetModel(float angle, glm::vec3 axis, glm::vec3 position, glm::vec3 scale)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, scale);
}

void Object::SetShader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	shader = new Shader(vertexShaderFile, fragmentShaderFile);
}

void Object::SetShader(Shader* shader)
{
	this->shader = shader;
}

void Object::AddTexture(Texture* texture) {
	textures.push_back(texture);
}