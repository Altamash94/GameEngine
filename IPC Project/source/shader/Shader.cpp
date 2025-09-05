#include "Shader.h"
#include <unistd.h>


Shader::Shader() {
	success = true;
	vertexShader = -1;
	fragmentShader = -1;
	ID = -1;
	vertexShaderSource = nullptr;
	fragmentShaderSource = nullptr;
}

Shader::~Shader()
{
	std::cout << "Deleting program ID: " << ID << std::endl;
	glDeleteProgram(ID);
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	success = true;
	vertexShader = -1;
	if (!CompilerShader(vertexPath, fragmentPath)) {
		std::cerr << "Shader program creation failed!" << std::endl;
		ID = 0; // Mark as invalid
	}

	glValidateProgram(ID); // only if compiled and linked successfully
}


bool Shader::CompilerShader(const char* vertexPath, const char* fragmentPath)
{
	success = true;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	ID = glCreateProgram();
	std::string vertexSource = GetSource(vertexPath);
	std::string fragmentSource = GetSource(fragmentPath);
	vertexShaderSource = vertexSource.c_str();
	fragmentShaderSource = fragmentSource.c_str();
	vname = vertexShaderSource;
	fname = fragmentShaderSource;

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	if (!checkCompileErrors(vertexShader, GL_VERTEX_SHADER))
	{
		success = false;
		std::cout << vertexPath << "Compilation failed" << std::endl;
		throw std::runtime_error("Shader compilation failed");
		return false;
	}
	
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	if (!checkCompileErrors(fragmentShader, GL_FRAGMENT_SHADER))
	{
		success = false;
		std::cout << fragmentPath << "Compilation failed" << std::endl;
		throw std::runtime_error("Shader compilation failed");
		return false;
	}

	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	
	if (!checkCompileErrors(ID, GL_PROGRAM))
	{
		success = false;
		return false;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return true;
}

void Shader::use() const
{
	glUseProgram(ID);
}

bool Shader::checkCompileErrors(unsigned int shader, unsigned int ShaderType)
{
	char infoLog[512];
	int success;

	if (ShaderType == GL_PROGRAM)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			std::cout << "Shader Program Linking Failed\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		if (ShaderType == GL_VERTEX_SHADER)
			std::cout << "Vertex Shader Compilation Failed\n" << infoLog << std::endl;
		else if (ShaderType == GL_FRAGMENT_SHADER)
			std::cout << "Fragment Shader Compilation Failed\n" << infoLog << std::endl;
		else
			std::cout << "Shader Compilation Failed\n" << infoLog << std::endl;
		return false;
	}

	return true;
}

std::string Shader::GetSource(const char* path)
{
	std::fstream file(path, std::ios::in);
    if (file.is_open() && file.good()) // ADDED file.good() check
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    else
    {
        std::cout << "Failed to open shader file: " << path << std::endl;
        perror("File open error"); // ADDED
    }
    return std::string();
}

bool Shader::SetInt(const std::string& name, int value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		std::cout << "Uniform " << name << " not found in shader program" << std::endl;
		return false;
	}
	glUniform1i(location, value);
	return true;
}

bool Shader::SetMat4(const std::string& name, glm::mat4 value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
	if (location == -1)
	{
		return false;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

bool Shader::SetVec3(const std::string &name, glm::vec3 value) const
{
	unsigned int location = glGetUniformLocation(ID, name.c_str());
    if (location == -1)
    {
        std::cout << "Uniform " << name << " not found in shader program" << std::endl;
		//PrintAllUniforms();
		return false;
    }
    glUniform3fv(location, 1, glm::value_ptr(value));
    return true;
}

void Shader::PrintAllUniforms() const{

	std::cout << vname << std::endl;
	std::cout << fname << std::endl;

    GLint count;
    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);

    std::cout << "Active Uniforms: " << count << std::endl;

    const GLsizei bufSize = 256; // max name length
    GLchar name[bufSize];
    GLsizei length;
    GLint size;
    GLenum type;

    for (GLint i = 0; i < count; ++i) {
        glGetActiveUniform(ID, i, bufSize, &length, &size, &type, name);

        GLint location = glGetUniformLocation(ID, name);

        std::cout << "Uniform #" << i << ": " << name 
                  << ", Type: " << type 
                  << ", Size: " << size 
                  << ", Location: " << location << std::endl;
    }
}