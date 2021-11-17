#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Light
{
	glm::vec3 lightColor = glm::vec3(1, 1, 1);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);
	float lightRotateAngle = 0.0f;
};

