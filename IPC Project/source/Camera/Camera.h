#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Camera
{
public:
	Camera(int width, int height);
	Camera();
	enum MoveDirection { FRONT, BACK, LEFT, RIGHT };
	void Move(MoveDirection direciton, double deltaTime);
	void CursorMovement(double xPos, double yPos, float deltaTime);
	float sensitivity;
	glm::vec3 position;	
	glm::vec3 cameraFront;
	virtual glm::mat4 GetViewMatrix() const;
	virtual void DrawDebug() = 0;
	virtual void DrawCameraOrientation() = 0;
	glm::mat4 GetProjectionMatrix() const{ return projection; };
	int width, height;
protected:
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	virtual void updateCameraVectors();
	double xOffset, yOffset, lastX, lastY;
	bool firstMouse;
	double yaw, pitch;
	float fovy, aspect, near, far;
	glm::mat4 projection;
};

#endif // !CAMERA_H