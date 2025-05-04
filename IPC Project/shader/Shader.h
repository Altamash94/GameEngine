#ifndef SHADER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader
{
	
public:
	unsigned int ID;
	bool success;
	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	void use() const;
	bool SetInt(const std::string& name, int value) const;
	bool SetMat4(const std::string& name, glm::mat4 value) const;
private:
	bool checkCompileErrors(unsigned int shader, unsigned int type);
	unsigned int vertexShader, fragmentShader;
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	std::string GetSource(const char* path);
	bool CompilerShader(const char* vertexPath, const char* fragmentPath);
};
#define SHADER_H
#endif // !SHADER_H