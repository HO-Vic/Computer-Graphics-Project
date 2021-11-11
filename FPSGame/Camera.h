#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Camera
{
	glm::vec3 pos = glm::vec3(0,0,0);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
private:
	glm::vec3 cameraDir;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;

public:
	void setCameraDir(glm::vec3 AT);
	void setCameraRight();
	void setCameraUp();
	glm::mat4 getCameraViewMatrix(glm::vec3 AT);
};

