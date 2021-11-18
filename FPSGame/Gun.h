#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
class Gun
{
protected:
	glm::vec3 pos = glm::vec3(0, 0, 0);
	float gunAngleX = 0.0f;
	float gunAngleY = 0.0f;
	float gunAngleZ = 0.0f;
	bool isAttack = false;
protected://shader binding
	GLuint gunVAO;
	GLuint gunVertexVBO;
	GLuint gunNormalVBO;
	std::vector<glm::vec3> gunVertexData;
	std::vector<glm::vec3> gunNormalData;
public://virtual func - status
	virtual void AttackMotion();
	virtual void reroad();
	virtual void playerRun();
public://virtual func - sound
	virtual void shootSound();
	virtual void reroadSound();
public://render
	virtual void renderGun(ShaderFunc& shaderID);
public://binding
	virtual void bindingGun(ShaderFunc& shaderID);
};

