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
	gunMatrix = glm::scale(gunMatrix, glm::vec3(0.1, 0.1, 0.1));	
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(gunAngleY), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(gunAngleX), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(gunAngleZ), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 0);
	shaderID.setTransMatrix(gunMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glDrawArrays(GL_TRIANGLES, 0, gunVertexData.size());
}

void Pistol::bindingGun(ShaderFunc& shaderID)
{
	readTriangleObj("obj_pistol_2.obj", gunVertexData, gunNormalData);
	//임시 텍스쳐 객체들
	std::vector<glm::vec3> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(gunVAO, gunVertexVBO, textureVboTemp, gunNormalVBO, gunVertexData, textureTemp, gunNormalData);
}
