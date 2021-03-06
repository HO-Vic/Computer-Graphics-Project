#include "Sniper.h"

void Sniper::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos;
}

void Sniper::AttackMotion()
{
	if (motionRevolu >= 0.1f)
		motionRevolu -= 0.1f;
}

void Sniper::setStatusAttack(bool f)
{
	isAttack = f;
	if (isAttack)
		motionRevolu += recoil;
}

void Sniper::reroad()
{
}

void Sniper::playerRun()
{
}

void Sniper::shootSound()
{
}

void Sniper::reroadSound()
{
}

void Sniper::renderGun(ShaderFunc& shaderID)
{
	recoil = 5.0f;
	glBindVertexArray(gunVAO);
	glm::mat4 gunMatrix = glm::mat4(1.0f);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE2);
	gunMatrix = glm::translate(gunMatrix, pos);

	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.x + motionRevolu), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.z), glm::vec3(0, 0, 1));

	gunMatrix = glm::translate(gunMatrix, glm::vec3(0.067f, -0.4f, -0.42f));

	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.x + defaultRotateAngleX), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::scale(gunMatrix, defaultScale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.y + rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.x + rotateAngle.x + motionRevolu + defaultRotateAngleX), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.z + rotateAngle.z), glm::vec3(0, 0, 1));
	shaderID.setTransMatrix(gunMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 2);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 3);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE8);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureN"), 8);
	glUniform1f(glGetUniformLocation(shaderID.getShaderID(), "ambientLight"), 0.4f);
	glDrawArrays(GL_TRIANGLES, 0, gunVertexData.size());
}

void Sniper::bindingGun(ShaderFunc& shaderID)
{
	readTriangleObj("obj_sniper.obj", gunVertexData, gunTextureData, gunNormalData);
	shaderID.InitBuffer(gunVAO, gunVertexVBO, gunTextureVBO, gunNormalVBO, gunVertexData, gunTextureData, gunNormalData);
}
