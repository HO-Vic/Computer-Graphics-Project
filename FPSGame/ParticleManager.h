#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<vector>
#include<queue>
#include<random>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"Particle.h"
class ParticleManager
{
	std::queue<Particle> particleQ;
	std::queue<Particle> flyrobotParticleQ;
	std::queue<Particle> bossParticleQ;
	GLuint vao;
	GLuint vertexVbo;
	GLuint normalVbo;
	std::vector<glm::vec3> vertexData;
	std::vector<glm::vec3> normalData;
public://render
	void renderParticles(ShaderFunc& shaderID);
	void renderParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir);
	void renderFlyRobotParticles(ShaderFunc& shaderID);
	void renderFlyRobotParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir);
	void renderBossParticles(ShaderFunc& shaderID);
	void renderBossParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir);
public://binding
	void bindingParticle(ShaderFunc& shaderID);
public:
	void Makeparticle(glm::vec3 pos,  glm::vec3 gunDir, glm::vec3 gunRight, glm::vec3 gunUp);
	void flyRobotParticle(glm::vec3 pos);
	void makeBossParticle(glm::vec3 pos);
	void parLife();
	void parFlyRobotLife();
	void parBossLife();
};

