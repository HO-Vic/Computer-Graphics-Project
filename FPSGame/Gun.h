#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Gun
{
	glm::vec3 pos = glm::vec3(0, 0, 0);
	float rotateAngleX = 0.0f;
	float rotateAngleY = 0.0f;
	float rotateAngleZ = 0.0f;
	bool isAttack = false;
public://virtual func
	virtual void Attack();
	virtual void reroad();
	virtual void playerRun();
};

