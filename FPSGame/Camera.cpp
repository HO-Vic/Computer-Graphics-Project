#include "Camera.h"

void Camera::setCameraDir()
{
	glm::mat4 rotateMat = glm::mat4(1.0f);
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.x), glm::vec3(1, 0, 0));
	rotateMat = glm::rotate(rotateMat, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	glm::vec3 newAT = glm::vec3(rotateMat * glm::vec4(AT, 1));
	cameraDir = glm::normalize(pos - newAT);//n
}

void Camera::setCameraRight()
{
	cameraRight= glm::normalize(glm::cross(up, glm::normalize(cameraDir)));//v
}

void Camera::setCameraUp()
{
	cameraUp = glm::cross(glm::normalize(cameraDir), cameraRight);
}

void Camera::renderCamera(ShaderFunc&  ShaderID)
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	glm::mat4 cameraView = glm::mat4(1.0f);
	cameraView = glm::lookAt(pos, -cameraDir + pos, cameraUp);
	unsigned int cameraViewLocation = glGetUniformLocation(ShaderID.getShaderID(), "viewTransform");
	glUniformMatrix4fv(cameraViewLocation, 1, GL_FALSE, glm::value_ptr(cameraView));
	unsigned int cameraPosLocation = glGetUniformLocation(ShaderID.getShaderID(), "cameraPos");
}

void Camera::moveFrontCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= walkRatio * glm::vec3(glm::normalize(cameraDir).x, 0 , glm::normalize(cameraDir).z);
	AT = pos - glm::vec3(0, 0, -0.2f);
	std::cout << cameraDir.x << ' ' << cameraDir.z << std::endl;
}

void Camera::moveBackCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += walkRatio * glm::vec3(glm::normalize(cameraDir).x, 0, glm::normalize(cameraDir).z);
	AT = pos - glm::vec3(0, 0, -0.2f);
}

void Camera::moveLeftCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos -= walkRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT = pos - glm::vec3(0, 0, -0.2f);
}

void Camera::moveRightCamera()
{
	setCameraDir();
	setCameraRight();
	setCameraUp();
	pos += walkRatio * glm::vec3(cameraRight.x, 0, cameraRight.z);
	AT = pos - glm::vec3(0, 0, -0.2f);
}

void Camera::rotateCamera(glm::vec3 rotateA)
{
	rotateAngle += rotateA;
}

glm::vec3 Camera::getPos()
{
	return pos;
}
