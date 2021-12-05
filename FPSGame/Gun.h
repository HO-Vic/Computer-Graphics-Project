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
	float motionRevolu = 0.0f;
	float defaultRotateAngleX = -20.0f;
	bool isAttack = false;
	float recoil = 0.0f;
protected://shader binding
	GLuint gunVAO;
	GLuint gunVertexVBO;
	GLuint gunNormalVBO;
	GLuint gunTextureVBO;
	std::vector<glm::vec3> gunVertexData;
	std::vector<glm::vec3> gunNormalData;
	std::vector<glm::vec2> gunTextureData;
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
	void initRecoilRotate();
	virtual void setStatusAttack(bool f) = 0;
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
public:
	float getRecoil();
public:
	glm::vec3 getAngles();
	glm::vec3 getPos();
	glm::vec3 getRevolu();
	float getMotionR();
};

