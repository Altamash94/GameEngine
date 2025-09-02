#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../shader/Shader.h"
#ifndef SHADER_DIR
#define SHADER_DIR "/home/altamash/Documents/CMakeTest/build/install/bin/shader/"
#endif

class Camera
{
public:
	Camera();
	enum MoveDirection { FRONT, BACK, LEFT, RIGHT };
	void Move(MoveDirection direciton, double deltaTime);
	void CursorMovement(double xPos, double yPos, float deltaTime);
	float sensitivity;
	glm::vec3 position;	
	glm::vec3 cameraFront;
	virtual glm::mat4 GetViewMatrix() const;
	virtual void DrawDebug() = 0;
	Shader debugShader;
protected:
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	virtual void updateCameraVectors();
	double xOffset, yOffset, lastX, lastY;
	bool firstMouse;
	double yaw, pitch;
};

#endif // !CAMERA_H