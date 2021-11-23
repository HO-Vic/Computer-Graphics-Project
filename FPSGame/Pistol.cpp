#include "Pistol.h"

void Pistol::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos + glm::vec3(0.05f, -0.2f, -0.2f);
}

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
	gunMatrix = glm::translate(gunMatrix, glm::vec3(-0.05f, 0.2f, 0.2f));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.x), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::translate(gunMatrix, glm::vec3(0.05f, -0.2f, -0.2f));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.x + defaultRotateAngleX), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::scale(gunMatrix, defaultScale);	
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.y + rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.x + rotateAngle.x + defaultRotateAngleX), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.z + rotateAngle.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 0);
	shaderID.setTransMatrix(gunMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glDrawArrays(GL_TRIANGLES, 0, gunVertexData.size());
}

void Pistol::bindingGun(ShaderFunc& shaderID)
{
	readTriangleObj("obj_pistol_3.obj", gunVertexData, gunNormalData);
	//임시 텍스쳐 객체들
	std::vector<glm::vec3> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(gunVAO, gunVertexVBO, textureVboTemp, gunNormalVBO, gunVertexData, textureTemp, gunNormalData);
}
