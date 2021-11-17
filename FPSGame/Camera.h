#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
class Camera
{
private:
	glm::vec3 pos = glm::vec3(0,1.0f,3.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
private:
	glm::vec3 cameraDir;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;

private:
	void setCameraRight();
	void setCameraUp();
public:
	void setCameraDir(glm::vec3 AT);
	void renderCamera(ShaderFunc& shaderID, glm::vec3 AT);
};

