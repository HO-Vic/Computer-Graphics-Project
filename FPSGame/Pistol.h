#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"Gun.h"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
class Pistol : public Gun
{
	//총은 공전으로 해야됨 수정
private://default trans
	glm::vec3 defaultScale = glm::vec3(0.1f, 0.1f, 0.1f);
	float defaultRotateAngleY = 90.0f;
public:
	Pistol(glm::vec3 playerPos): Gun(playerPos) {}
public://virtual func - status
	void  AttackMotion() override;
	void  reroad() override;
	void  playerRun() override;
public://virtual func - sound
	void shootSound() override;
	void reroadSound() override;
public://render
	void renderGun(ShaderFunc& shaderID) override;
public://binding
	void bindingGun(ShaderFunc& ) override;
};

