#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
//#include"Gun.h"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
//#define STB_IMAGE_IMPLEMENTATION
//#include"stb_image.h"
class Bullet
{
private:
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 rotateAngle = glm::vec3(0, 0, 0);
private://shader binding
	GLuint bulletVAO;
	GLuint bulletVertexVBO;
	GLuint bulletNormalVBO;
	GLuint bulletTextureVBO;
	std::vector<glm::vec3> bulletVertexData;
	std::vector<glm::vec3> bulletNormalData;
	std::vector<glm::vec2> bulletTextureData;
public:
	Bullet(glm::vec3 playerPos) : pos(playerPos) {}
public://render
	void renderBullet(ShaderFunc& shaderID);
public://binding
	void bindingBullet(ShaderFunc& shaderID);
};

