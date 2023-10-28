#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
class CrossHead
{//cross header

	GLuint dotVao;
	GLuint dotVbo;
	GLuint dotNormalVbo;

	GLuint sniperDotVao;
	GLuint sniperDotVbo;
	GLuint sniperDotNormalVbo;
	GLuint sniperDotTextureVbo;
	std::vector<glm::vec3> sniperDotVertexData;
	std::vector<glm::vec2> sniperDotTextureData;
	std::vector<glm::vec3> sniperDotNormalData;
public:
	void drawdotCrossHead(ShaderFunc& shaderID);
	void drawSniperCrossHead(ShaderFunc& shaderID);
	void binding(ShaderFunc& shaderID);
};


