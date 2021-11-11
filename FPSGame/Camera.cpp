#include "Camera.h"

void Camera::setCameraDir(glm::vec3 AT)
{
	cameraDir = glm::normalize(pos - AT);//n
}

void Camera::setCameraRight()
{
	cameraRight= glm::cross(up, cameraDir);//v
}

void Camera::setCameraUp()
{
	cameraUp = glm::cross(cameraDir, cameraRight);
}

glm::mat4 Camera::getCameraViewMatrix(glm::vec3 AT)
{
	setCameraDir(AT);
	setCameraRight();
	setCameraUp();
	glm::mat4 cameraView = glm::mat4(1.0f);
	cameraView = glm::lookAt(pos, AT, cameraUp);
	return cameraView;
}
