#include "Rifle.h"

void Rifle::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos + glm::vec3(0.07f, -0.3f, -0.2f);
}

void Rifle::AttackMotion()
{
	if (motionRevolu >= recoil)
		motionRevolu -= 0.1f;
}

void Rifle::setStatusAttack(bool f)
{
	isAttack = f;
	if (isAttack)
		motionRevolu += recoil;
}

void Rifle::reroad()
{
}

void Rifle::playerRun()
{
}

void Rifle::shootSound()
{
}

void Rifle::reroadSound()
{
}

void Rifle::renderGun(ShaderFunc& shaderID)
{
	recoil = 0.5f;
	glBindVertexArray(gunVAO);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE1);
	glm::mat4 gunMatrix = glm::mat4(1.0f);
	gunMatrix = glm::translate(gunMatrix, pos);
	gunMatrix = glm::translate(gunMatrix, glm::vec3(-0.1f, 0.3f, 0.2f));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.x + motionRevolu), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::translate(gunMatrix, glm::vec3(0.1f, -0.3f, -0.2f));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.x + defaultRotateAngleX), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::scale(gunMatrix, defaultScale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.y + rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.x + rotateAngle.x + motionRevolu), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.z + rotateAngle.z), glm::vec3(0, 0, 1));
	shaderID.setTransMatrix(gunMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 1);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, gunVertexData.size());
}

void Rifle::bindingGun(ShaderFunc& shaderID)
{
	readTriangleObj("obj_rifle.obj", gunVertexData, gunTextureData, gunNormalData);
	//임시 텍스쳐 객체들
	std::vector<glm::vec2> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(gunVAO, gunVertexVBO, textureVboTemp, gunNormalVBO, gunVertexData, gunTextureData, gunNormalData);
}
