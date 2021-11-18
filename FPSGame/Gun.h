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
	GLuint gunTextureVBO;
	std::vector<glm::vec3> gunVertexData;
	std::vector<glm::vec3> gunNormalData;
	std::vector<glm::vec3> gunTextureData;
public://virtual func - status
	virtual void AttackMotion() = 0;
	virtual void reroad() = 0;
	virtual void playerRun() = 0;
public://virtual func - sound
	virtual void shootSound() = 0;
	virtual void reroadSound() = 0;
public://render
	virtual void renderGun(ShaderFunc& shaderID) = 0;
public://binding
	virtual void bindingGun(ShaderFunc& shaderID) = 0;
};

