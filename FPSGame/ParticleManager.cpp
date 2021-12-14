#include "ParticleManager.h"

void ParticleManager::renderParticles(ShaderFunc& shaderID)
{
	int qsize = particleQ.size();
	for (int i = 0; i < qsize; i++) {
		Particle temp = particleQ.front();
		particleQ.pop();
		for (int j = 0; j < 20; j++) {
			renderParticle(shaderID, temp.getPos(), (float)temp.getLife() * temp.getDir()[j]);
		} 
		particleQ.push(temp);
	}
}

void ParticleManager::renderParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> red(0.7f, 1.0f);
	std::uniform_real_distribution<float> green(0.1f, 0.7f);

	glBindVertexArray(vao);
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, pos + dir);
	matrix = glm::scale(matrix, glm::vec3(0.002f, 0.002f, 0.002f));
	shaderID.setTransMatrix(matrix);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), red(dre),  green(dre), 0);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), -1);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
}

void ParticleManager::renderFlyRobotParticles(ShaderFunc& shaderID)
{
	int qsize = flyrobotParticleQ.size();
	for (int i = 0; i < qsize; i++) {
		Particle temp = flyrobotParticleQ.front();
		flyrobotParticleQ.pop();
		for (int j = 0; j < 20; j++) {
			renderFlyRobotParticle(shaderID, temp.getPos(), (float)temp.getLife() * temp.getDir()[j]);
		}
		flyrobotParticleQ.push(temp);
	}
}

void ParticleManager::renderFlyRobotParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> red(0.8f, 1.0f);
	std::uniform_real_distribution<float> green(0.1f, 0.5f);

	glBindVertexArray(vao);
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, pos + dir);
	matrix = glm::scale(matrix, glm::vec3(0.05f, 0.05f, 0.05f));
	shaderID.setTransMatrix(matrix);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), red(dre), green(dre), 0);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), -1);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
}

void ParticleManager::renderBossParticles(ShaderFunc& shaderID)
{
	int qsize = bossParticleQ.size();
	for (int i = 0; i < qsize; i++) {
		Particle temp = bossParticleQ.front();
		bossParticleQ.pop();
		for (int j = 0; j < 20; j++) {
			renderBossParticle(shaderID, temp.getPos(), (float)temp.getLife() * temp.getDir()[j]);
		}
		bossParticleQ.push(temp);
	}
}

void ParticleManager::renderBossParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> red(0.8f, 1.0f);
	std::uniform_real_distribution<float> green(0.1f, 0.5f);

	glBindVertexArray(vao);
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, pos + dir);
	matrix = glm::scale(matrix, glm::vec3(0.1f, 0.1f, 0.1f));
	shaderID.setTransMatrix(matrix);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), red(dre), green(dre), 0);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), -1);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
}

void ParticleManager::bindingParticle(ShaderFunc& shaderID)
{
	GLuint temp;
	std::vector<glm::vec2> tempT;
	readTriangleObj("obj_particle.obj", vertexData, tempT, normalData);
	shaderID.InitBuffer(vao, vertexVbo, temp, normalVbo, vertexData, tempT, normalData);
}

void  ParticleManager::Makeparticle(glm::vec3 pos, glm::vec3 gunDir, glm::vec3 gunRight, glm::vec3 gunUp)
{
	if (particleQ.size() <= 6)
		particleQ.push(Particle(pos + gunDir + 0.05f * gunRight, gunDir, gunRight, gunUp));
}

void ParticleManager::flyRobotParticle(glm::vec3 pos)
{
	flyrobotParticleQ.push(Particle(pos, glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
}

void ParticleManager::makeBossParticle(glm::vec3 pos)
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_real_distribution<float> ureX(-5, 5);
	std::uniform_real_distribution<float> ureY(-4, 1);
	std::uniform_real_distribution<float> ureZ(-5, 5);
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
	bossParticleQ.push(Particle(pos+glm::vec3(ureX(dre), ureY(dre), ureZ(dre)), glm::vec3(0, 0, 1.3), glm::vec3(1.3, 0, 0), glm::vec3(0, 1.3, 0)));
}

void ParticleManager::parLife()
{
	for (int i = 0; i < particleQ.size(); i++) {
		Particle temp = particleQ.front();
		particleQ.pop();
		temp.setLife();
		if(temp.getLife() < 5)
			particleQ.push(temp);
	}
}

void ParticleManager::parFlyRobotLife()
{
	for (int i = 0; i < flyrobotParticleQ.size(); i++) {
		Particle temp = flyrobotParticleQ.front();
		flyrobotParticleQ.pop();
		temp.setLife();
		if (temp.getLife() < 25)
			flyrobotParticleQ.push(temp);
	}
}

void ParticleManager::parBossLife()
{
	for (int i = 0; i < bossParticleQ.size(); i++) {
		Particle temp = bossParticleQ.front();
		bossParticleQ.pop();
		temp.setLife();
		if (temp.getLife() < 200)
			bossParticleQ.push(temp);
	}
}
