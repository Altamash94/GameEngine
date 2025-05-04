#include "Camera.h"


Camera::Camera()
{
	position = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	cameraFront = glm::vec3(0) - position;
	xOffset = 0.0f;
	yOffset = 0.0f;
	firstMouse = true;
	lastX = -1;
	lastY = -1;
	yaw = -89.0f;
	pitch = 0.0f;
	sensitivity = 0.1f;
}

void Camera::Move(MoveDirection direction, double deltaTime)
{
	switch (direction)
	{
	case MoveDirection::FRONT:
		position +=  cameraFront * static_cast<float>(deltaTime);
		break;
	case MoveDirection::BACK:
		position -= cameraFront * static_cast<float>(deltaTime);
		break;
	case MoveDirection::LEFT:
		position -= cameraRight * static_cast<float>(deltaTime);
		break;
	case MoveDirection::RIGHT:
		position += cameraRight * static_cast<float>(deltaTime);
		break;
	}

}


void Camera::CursorMovement(double xPos, double yPos)
{
	if (firstMouse)
	{
		firstMouse = false;
		lastX = xPos;
		lastY = yPos;
		return;
	}

	xOffset = (xPos - lastX) * sensitivity;
	yOffset = (lastY - yPos) * sensitivity; // reversed since y-coordinates go from bottom to top
	lastX = xPos;
	lastY = yPos;
	yaw += xOffset;
	pitch += yOffset;
	
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	
	updateCameraVectors();
}

void Camera::updateCameraVectors()
{
	glm::vec3 direction(0);
	direction.x = static_cast<float>(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	direction.y = static_cast<float>(sin(glm::radians(pitch)));
	direction.z = static_cast<float>(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
	cameraFront = glm::normalize(direction);
	cameraRight = glm::normalize(glm::cross(cameraFront, glm::vec3(0, 1, 0)));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}