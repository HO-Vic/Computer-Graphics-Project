#include "Pistol.h"

void Pistol::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos ;
}

void Pistol::setStatusAttack(bool f)
{
	isAttack = f;
	if (isAttack)
		motionRevolu += recoil;
}

void Pistol::AttackMotion()
{
	if(motionRevolu >= 0.1f)
		motionRevolu -= 0.1f;
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

void Pistol::setTexture()
{

}

void Pistol::renderGun(ShaderFunc& shaderID)
{
	recoil = 1.4f;
	glBindVertexArray(gunVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE0);
	glm::mat4 gunMatrix = glm::mat4(1.0f);
	gunMatrix = glm::translate(gunMatrix, pos);

	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.x + motionRevolu), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(revoluAngle.z), glm::vec3(0, 0, 1));

	gunMatrix = glm::translate(gunMatrix, glm::vec3(0.02f, -0.11f, -0.12f));

	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.x + defaultRotateAngleX), glm::vec3(1, 0, 0));
	gunMatrix = glm::rotate(gunMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	gunMatrix = glm::scale(gunMatrix, defaultScale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.y + rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.x + rotateAngle.x + defaultRotateAngleX + motionRevolu), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(revoluAngle.z + rotateAngle.z), glm::vec3(0, 0, 1));
	shaderID.setTransMatrix(gunMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 0);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 3);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE7);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureN"), 7);
	glUniform1f(glGetUniformLocation(shaderID.getShaderID(), "ambientLight"), 0.3f);
	glDrawArrays(GL_TRIANGLES, 0, gunVertexData.size());
}

void Pistol::bindingGun(ShaderFunc& shaderID)
{
	readTriangleObj("obj_pistol.obj", gunVertexData, gunTextureData, gunNormalData);
	shaderID.InitBuffer(gunVAO, gunVertexVBO, gunTextureVBO, gunNormalVBO, gunVertexData, gunTextureData, gunNormalData);	
}
