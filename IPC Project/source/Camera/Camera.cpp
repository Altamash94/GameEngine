#include "Camera.h"


Camera::Camera(int width, int height): width(width), height(height)
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
#if defined(_WIN32)
	sensitivity = 0.05f;
#elif defined(__linux__)
	sensitivity = 0.05f;
#else
	sensitivity = 1.0f;
#endif
	std::cout << "cursor sesitivity " << sensitivity << std::endl;

	aspect = (float)width / (float)height;
    fovy = glm::radians(45.0f);
	near = 0.05f;
	far = 100.0f;
    projection = glm::perspective(fovy, aspect, near, far);
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
	xOffset = (xPos - lastX) * sensitivity;// * deltaTime;
	yOffset = (lastY - yPos) * sensitivity;// * deltaTime; // reversed since y-coordinates go from bottom to top
	lastX = xPos;
	lastY = yPos;
	yaw += xOffset;
	pitch += yOffset;
	
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;
	if (yaw > 360.0f) yaw -= 360.0f;
	if (yaw < 0.0f)yaw += 360.0f;

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

Camera::Camera()
{
}

void Camera::DrawDebug(){}
void Camera::DrawCameraOrientation(){}
Camera::~Camera()
{
	std::cout << "Deleting camera" << std::endl;
}