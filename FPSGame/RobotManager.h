#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
#include<string>
#include"Robot.h"
class RobotManager
{
	GLuint robotHeadVAO;
	GLuint robotHeadVertexVBO;
	GLuint robotHeadNormalVBO;
	GLuint robotHeadTextureVBO;
	std::vector<glm::vec3> robotHeadVertexData;
	std::vector<glm::vec3> robotHeadNormalData;
	std::vector<glm::vec2> robotHeadTextureData;

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

	GLuint robotLegLVAO;
	GLuint robotLegLVertexVBO;
	GLuint robotLegLNormalVBO;
	GLuint robotLegLTextureVBO;
	std::vector<glm::vec3> robotLegLVertexData;
	std::vector<glm::vec3> robotLegLNormalData;
	std::vector<glm::vec2> robotLegLTextureData;

	GLuint robotLegRVAO;
	GLuint robotLegRVertexVBO;
	GLuint robotLegRNormalVBO;
	GLuint robotLegRTextureVBO;
	std::vector<glm::vec3> robotLegRVertexData;
	std::vector<glm::vec3> robotLegRNormalData;
	std::vector<glm::vec2> robotLegRTextureData;
	Robot robotHead[20];
	Robot robotbody[20];
	Robot robotLArm[20];
	Robot robotRArm[20];
	Robot robotLegR[20];
	Robot robotLegL[20];

private:
	void bindingEnemy(ShaderFunc& shaderID, std::string name);
public:
	void renderEnemys(ShaderFunc& shderID);
	void bindingEnemys(ShaderFunc& shaderID);
	Robot* getRobot();
	void setParent();
	RobotManager();


};
