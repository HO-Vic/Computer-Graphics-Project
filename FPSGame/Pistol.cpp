#include "Pistol.h"

void Pistol::AttackMotion()
{
}

void Pistol::reroad()
{
}

void Pistol::playerRun()
{
}

void Pistol::shootSound()
{
}

void Pistol::reroadSound()
{
}

void Pistol::renderGun(ShaderFunc& shaderID)
{
	glBindVertexArray(gunVAO);
	glm::mat4 gunMatrix = glm::mat4(1.0f);
	gunMatrix = glm::translate(gunMatrix, pos);
	gunMatrix = glm::rotate(gunMatrix, glm::radians(gunAngleY), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(gunAngleX), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(gunAngleZ), glm::vec3(0, 0, 1));
	gunMatrix = glm::scale(gunMatrix, glm::vec3(0.5, 0.5, 0.5));
	unsigned int transMatrixLocation = glGetUniformLocation(shaderID.getShaderID(), "modelTransform");
	glUniformMatrix4fv(transMatrixLocation, 1, GL_FALSE, glm::value_ptr(gunMatrix));
	glDrawArrays(GL_QUADS, 0, gunVertexData.size());
}

void Pistol::bindingGun(ShaderFunc& shaderID)
{
	readQuadObj("obj_pistol.obj", gunVertexData, gunNormalData);
	std::vector<glm::vec3> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(gunVAO, gunVertexVBO, gunNormalVBO, textureVboTemp, gunVertexData, gunNormalData, textureTemp);
	//glGenVertexArrays(1, &gunVAO);
	//glBindVertexArray(gunVAO);
	//glGenBuffers(1, &gunVertexVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, gunVertexVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * gunVertexData.size(), &gunVertexData[0], GL_STREAM_DRAW);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//glEnableVertexAttribArray(0);
	//glGenBuffers(1, &gunNormalVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, gunNormalVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * gunNormalData.size(), &gunNormalData[0], GL_STREAM_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	//glEnableVertexAttribArray(1);
}
