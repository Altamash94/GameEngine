#include "Camera.h"


Camera::Camera():
debugShader(SHADER_DIR"lineVertex.glsl", SHADER_DIR"lineFragment.glsl")
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
	sensitivity = 0.005f;
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


void Camera::CursorMovement(double xPos, double yPos, float deltaTime)
{
	//Debug
	glm::vec3 start = position;
	glm::vec3 end = position + cameraFront * 0.5f; // Short arrow
	//
	if (firstMouse)
	{
		firstMouse = false;
		lastX = xPos;
		lastY = yPos;
		return;
	}
	//std::cout << "PosXY (" << xPos << ", " << yPos << ")" << std::endl;
	//std::cout << "LastXY (" << lastX << ", " << lastY << ")" << std::endl;
	xOffset = (xPos - lastX) * sensitivity;// * deltaTime;
	yOffset = (lastY - yPos) * sensitivity;// * deltaTime; // reversed since y-coordinates go from bottom to top
	lastX = xPos;
	lastY = yPos;
	yaw += xOffset;
	pitch += yOffset;
	
	if (pitch > 89.0f)
	pitch = 89.0f;
	if (pitch < -89.0f)
	pitch = -89.0f;
	//debug
	//float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	//float y = sin(glm::radians(pitch));  // Vertical component
	//std::cout << "Offset (" << xOffset << ", " << yOffset << ")" << std::endl;
	//std::cout << "yaw, pitch (" << yaw << ", " << pitch << ")" << std::endl;
	//std::cout << "(x,y) (" << x << ", " << y << ")" << std::endl;
	//std::cout << std::endl;

	
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

glm::mat4 Camera::GetViewMatrix() const
	{
		return glm::lookAt(position, position + cameraFront, cameraUp);
	}