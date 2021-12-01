#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<queue>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"BulletInfo.h"

class Bullet
{
	std::queue<BulletInfo> bullets;
private://shader binding
	GLuint bulletVAO;
	GLuint bulletVertexVBO;
	GLuint bulletNormalVBO;
	GLuint bulletTextureVBO;
	std::vector<glm::vec3> bulletVertexData;
	std::vector<glm::vec3> bulletNormalData;
	std::vector<glm::vec2> bulletTextureData;
private:
	void renderBullet(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 rotateAngle);
public://render
	void renderBullets(ShaderFunc& shaderID);
public://binding
	void bindingBullet(ShaderFunc& shaderID);
public:
	void addBullet(glm::vec3 cameraPos, glm::vec3 dir, glm::vec3 angle);
	 void moveBullets();
};

