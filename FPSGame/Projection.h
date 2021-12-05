#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
class Projection {
public:
	void perspectriveProjection(ShaderFunc& shaderID, int Wwdith, int Wheight, float fovy);
	void orthoProjection(ShaderFunc& shaderID, int Wwdith, int Wheight);
};

