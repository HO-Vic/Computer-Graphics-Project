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
		temp.setLife();
		if(temp.getLife() >= 30)
			particleQ.push(temp);
	}
}

void ParticleManager::renderParticle(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 dir)
{
	glBindVertexArray(vao);
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(0, 1.0f, 9.0f) + dir);
	matrix = glm::scale(matrix, glm::vec3(0.01f, 0.01f, 0.01f));
	shaderID.setTransMatrix(matrix);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), 0.5, 0.3, 0);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), -1);
	glDrawArrays(GL_TRIANGLES, 0, vertexData.size());
}

void ParticleManager::bindingParticle(ShaderFunc& shaderID)
{
	GLuint temp;
	std::vector<glm::vec3> tempN;
	std::vector<glm::vec2> tempT;
	readTriangleObj("obj_particle.obj", vertexData, tempT, tempN);
	shaderID.InitBuffer(vao, vertexVbo, temp, temp, vertexData, tempT, tempN);
}

void  ParticleManager::Makeparticle(glm::vec3 pos, glm::vec3 gunDir, glm::vec3 gunRight)
{
	if (particleQ.size() <= 30) {	
		particleQ.push(Particle(pos + gunDir + 0.002f * gunRight, gunDir, gunRight));
	}
}

void ParticleManager::parLife()
{
	for (int i = 0; i < particleQ.size(); i++) {
		Particle temp = particleQ.front();
		particleQ.pop();
		temp.setLife();
		particleQ.push(temp);
	}
}
