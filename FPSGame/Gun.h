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
	glm::vec3 rotateAngle = glm::vec3(0, 0, 0);
	glm::vec3 revoluAngle = glm::vec3(0, 0, 0);
	bool isAttack = false;
protected://shader binding
	GLuint gunVAO;
	GLuint gunVertexVBO;
	GLuint gunNormalVBO;
	GLuint gunTextureVBO;
	std::vector<glm::vec3> gunVertexData;
	std::vector<glm::vec3> gunNormalData;
	std::vector<glm::vec3> gunTextureData;
public:
	Gun(glm::vec3 playerPos): pos(playerPos) {}
public://set func
	void setRevoluAngleX(float Angle);
	void setRevoluAngleY(float Angle);
	void setRevoluAngleZ(float Angle);
public:
	void moveRevoluX(float Angle);
	void moveRevoluY(float Angle);
public:
	virtual void setPos(glm::vec3 inPutpos) = 0;
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

