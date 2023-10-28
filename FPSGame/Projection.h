#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"ShaderFunc.h"
class Projection {
public:
	void perspectriveProjection(ShaderFunc& shaderID, int Wwdith, int Wheight, float fovy);
	void orthoProjection(ShaderFunc& shaderID, int Wwdith, int Wheight);
};

