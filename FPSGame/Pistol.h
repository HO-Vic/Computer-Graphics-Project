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
private://default trans
	glm::vec3 defaultScale = glm::vec3(0.7f, 0.7f, 0.7f);
	float defaultRotateAngleY = 90.0f;

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

