#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
#include"FlyRobot.h"
#include<string>
class FlyRobotManager
{
	GLuint robotBodyVAO;
	GLuint robotBodyVertexVBO;
	GLuint robotBodyNormalVBO;
	GLuint robotBodyTextureVBO;
	std::vector<glm::vec3> robotBodyVertexData;
	std::vector<glm::vec3> robotBodyNormalData;
	std::vector<glm::vec2> robotBodyTextureData;

	GLuint robotArmLVAO;
	GLuint robotArmLVertexVBO;
	GLuint robotArmLNormalVBO;
	GLuint robotArmLTextureVBO;
	std::vector<glm::vec3> robotArmLVertexData;
	std::vector<glm::vec3> robotArmLNormalData;
	std::vector<glm::vec2> robotArmLTextureData;

	GLuint robotArmRVAO;
	GLuint robotArmRVertexVBO;
	GLuint robotArmRNormalVBO;
	GLuint robotArmRTextureVBO;
	std::vector<glm::vec3> robotArmRVertexData;
	std::vector<glm::vec3> robotArmRNormalData;
	std::vector<glm::vec2> robotArmRTextureData;

	GLuint robotSpinVAO;
	GLuint robotSpinVertexVBO;
	GLuint robotSpinNormalVBO;
	GLuint robotSpinTextureVBO;
	std::vector<glm::vec3> robotSpinVertexData;
	std::vector<glm::vec3> robotSpinNormalData;
	std::vector<glm::vec2> robotSpinTextureData;

	GLuint robotWeaponVAO;
	GLuint robotWeaponVBO;
	GLuint robotWeaponNormalVBO;
	GLuint robotWeaponTextureVBO;
	std::vector<glm::vec3> robotWeaponVertexData;
	std::vector<glm::vec3> robotWeaponNormalData;
	std::vector<glm::vec2> robotWeaponTextureData;

	Flyrobot flyrobotlarm[20];
	Flyrobot flyrobotrarm[20];
	Flyrobot flyrobotspin[20];
	Flyrobot flyrobotbody[20];
	Flyrobot flyrobotweapon[20];

public:
	void renderEnemys(ShaderFunc& shaderID);
	void bindingEnemys(ShaderFunc& shaderID);
private:
	void bindingEnemy(ShaderFunc& shaderID, string name);
public:
	Flyrobot* getFlyRobot();
	void setParent();
	void MinusHp();
	FlyRobotManager();
};

