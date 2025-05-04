#ifndef CAMERA_H


#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


class Camera
{
public:
	enum MoveDirection { FRONT, BACK, LEFT, RIGHT };
	Camera();
	void Move(MoveDirection direciton, double deltaTime);
	void CursorMovement(double xPos, double yPos);
	glm::mat4 GetViewMatrix() const
	{
		return glm::lookAt(position, position + cameraFront, cameraUp);
	}
	float sensitivity;
private:
	glm::vec3 position;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 cameraFront;
	void updateCameraVectors();
	double xOffset, yOffset, lastX, lastY;
	bool firstMouse;
	double yaw, pitch;
};
#define CAMERA_H
#endif // !CAMERA_H