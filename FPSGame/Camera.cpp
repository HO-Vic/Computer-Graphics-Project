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

void Camera::renderCamera(ShaderFunc&  ShaderID, glm::vec3 AT)
{
	setCameraDir(AT);
	setCameraRight();
	setCameraUp();
	glm::mat4 cameraView = glm::mat4(1.0f);
	cameraView = glm::lookAt(pos, -cameraDir, cameraUp);
	unsigned int cameraViewLocation = glGetUniformLocation(ShaderID.getShaderID(), "viewTransform");
	glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(cameraView));
	unsigned int cameraPosLocation = glGetUniformLocation(ShaderID.getShaderID(), "cameraPos");
}
