#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"Gun.h"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
class Rifle : public Gun
{
private://default trans
	glm::vec3 defaultScale = glm::vec3(0.07f, 0.07f, 0.07f);
	glm::vec3 defaultTrans = glm::vec3(0.07f, -0.3f, -0.2f);

	
public:
	Rifle(glm::vec3 playerPos) : Gun(playerPos) {}
public:
	void setPos(glm::vec3 inPutpos) override;
public://virtual func - status
	void  AttackMotion() override;
	void setStatusAttack(bool f);
	void  reroad() override;
	void  playerRun() override;
public://virtual func - sound
	void shootSound() override;
	void reroadSound() override;
public://render
	void renderGun(ShaderFunc& shaderID) override;
public://binding
	void bindingGun(ShaderFunc&) override;
};

