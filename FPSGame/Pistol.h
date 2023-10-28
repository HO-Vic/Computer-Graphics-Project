#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"Gun.h"
#include"ShaderFunc.h"
#include"readTriangleObj.h"

class Pistol : public Gun
{
private://default trans
	glm::vec3 defaultScale = glm::vec3(0.08f, 0.08f, 0.08f);
public:
	Pistol(glm::vec3 playerPos): Gun(playerPos) {}
public:
	void setPos(glm::vec3 inPutpos) override;
public://virtual func - status
	void setStatusAttack(bool f);
	void  AttackMotion() override;
	void  reroad() override;
	void  playerRun() override;
public://virtual func - sound
	void shootSound() override;
	void reroadSound() override;
public://texture
	void setTexture();
public://render
	void renderGun(ShaderFunc& shaderID) override;
public://binding
	void bindingGun(ShaderFunc& ) override;
};

