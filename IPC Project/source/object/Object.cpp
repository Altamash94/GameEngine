#include "Object.h"

Object::Object(const char* vertexShaderFile, const char* fragmentShaderFile):
shader(std::make_unique<Shader>(vertexShaderFile, fragmentShaderFile))
{
	model = glm::mat4(1.0f);
	VAO = 0u;
    VBO = 0u;
}

Object::~Object()
{
	std::cout << "Delete Object object" << std::endl;
	if (VAO != 0u) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0u;
    }
    if (VBO != 0u) {
        glDeleteBuffers(1, &VBO);
        VBO = 0u;
    }
}

void Object::SetModel(float angle, glm::vec3 axis, glm::vec3 position, glm::vec3 scale)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, angle, axis);
	model = glm::scale(model, scale);
}


void Object::AddTexture(const char* texturePath, const char* uniformName, int UniformID) {
	textures.push_back(std::make_unique<Texture>(texturePath, uniformName));
	shader->use();
	shader->SetInt(uniformName, UniformID);
}

void Object::SetCamera(std::shared_ptr<Camera> camera){
	this->camera = camera;
	shader->use();
	shader->SetMat4("projection", camera->GetProjectionMatrix());
	shader->SetMat4("view", camera->GetViewMatrix());
}

void Object::PreDrawCheckErrors() const{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "GL error pre-draw: " << std::hex << err << std::dec << std::endl;
    }

    const char* msg = "Before drawing line";
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 1,
                         GL_DEBUG_SEVERITY_NOTIFICATION, (GLsizei)strlen(msg), msg);
}

void Object::PostDrawCheckErrors() const{
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "GL error post-draw: " << std::hex << err << std::dec << std::endl;
    }

    const char* msg = "After drawing line";
    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 2,
                         GL_DEBUG_SEVERITY_NOTIFICATION, (GLsizei)strlen(msg), msg);
}