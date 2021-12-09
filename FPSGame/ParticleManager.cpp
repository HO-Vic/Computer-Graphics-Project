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
	matrix = glm::scale(matrix, glm::vec3(0.0035f, 0.0035f, 0.0035f));
	shaderID.setTransMatrix(matrix);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), red(dre),  green(dre), 0);
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
