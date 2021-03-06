#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
class Light
{
	glm::vec3 lightColor = glm::vec3(0.7, 0.7, 0.7);
	glm::vec3 lightPos = glm::vec3(0.0f, 3.0f, 0.0f);
	float lightRevoluAngle = 0.0f;
public://set
	void setLightRevoluAngle(float angle);
	void modifyLightRevolutAngle(float angle);
	void setLightPos(glm::vec3 Pos);
	void modifyLightPos(glm::vec3 Pos);
public://run
	void renderLight(ShaderFunc& shaderID);
};

