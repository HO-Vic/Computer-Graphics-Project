#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<random>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
class Particle
{
	glm::vec3 pos;
	glm::vec3 dir[20];
	int life = 0;
public:
	Particle(glm::vec3 gunHead, glm::vec3 gunDir, glm::vec3 gunRight, glm::vec3 gunUp) : pos(gunHead){
		std::random_device rd;
		std::default_random_engine dre(rd());
		std::uniform_real_distribution<float> urd(-1.0f, 1.0f);
		std::uniform_real_distribution<float> urdZ(0.0f, 1.0f);
		std::uniform_real_distribution<float> urdU(-1.0f, 1.0f);
		for (int i = 0; i < 20; i++) 
			dir[i] = 0.03f * urd(dre) * gunRight + 0.03f * urdZ(dre) * gunDir + 0.03f * urdU(dre) * gunUp;
	}
public:
	glm::vec3 getPos();
	glm::vec3* getDir();
	int getLife();
	void setLife();
};

