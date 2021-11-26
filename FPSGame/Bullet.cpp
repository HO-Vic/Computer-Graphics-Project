#include "Bullet.h"

void Bullet::renderBullet(ShaderFunc& shaderID)
{
	glm::mat4 bulletMatrix = glm::mat4(1.0f);
	bulletMatrix = glm::translate(bulletMatrix, pos);
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.x), glm::vec3(1, 0, 0));
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	//bulletMatrix = glm::scale(bulletMatrix, defaultScale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 0);
	shaderID.setTransMatrix(bulletMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glBindVertexArray(bulletVAO);
	glDrawArrays(GL_TRIANGLES, 0, bulletVertexData.size());
}

void Bullet::bindingBullet(ShaderFunc& shaderID)
{
	readTriangleObj("obj_bullet.obj", bulletVertexData, bulletNormalData);
	//임시 텍스쳐 객체들
	std::vector<glm::vec3> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(bulletVAO, bulletVertexVBO, textureVboTemp, bulletNormalVBO, bulletVertexData, textureTemp, bulletNormalData);
}
