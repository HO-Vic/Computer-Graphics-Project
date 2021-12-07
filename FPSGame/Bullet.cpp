#include "Bullet.h"

void Bullet::renderBullet(ShaderFunc& shaderID, glm::vec3 pos, glm::vec3 rotateAngle)
{
	glBindVertexArray(bulletVAO);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE3);
	glm::mat4 bulletMatrix = glm::mat4(1.0f);
	bulletMatrix = glm::translate(bulletMatrix, pos);
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.x), glm::vec3(1, 0, 0));
	bulletMatrix = glm::rotate(bulletMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	bulletMatrix = glm::scale(bulletMatrix, glm::vec3(0.5, 0.5, 0.5));
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(rotateAngle.z), glm::vec3(0, 0, 1));
	shaderID.setTransMatrix(bulletMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 3);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, bulletVertexData.size());
}

void Bullet::renderBullets(ShaderFunc& shaderID)
{
	for (int i = 0; i < bullets.size(); i++) {
		BulletInfo currentRenderGun = bullets.front();
		bullets.pop();
		renderBullet(shaderID, currentRenderGun.getPos(), currentRenderGun.getRotateAngle());
		//���࿡ �浹���� �ʾҴٸ� �Ǵ� �����Ÿ��� �ȵƴٸ� �ٽ� �ִ´� -> �����Ÿ��� dir���� ������ ���
		if (currentRenderGun.getDirUnit() <= 100)//�ʱ⿡�� 49�� ����
		//std::cout << i << "����" << std::endl;
	//	std::cout <<"x:"<< currentRenderGun.getPos().x<< std::endl;
		//std::cout << "y:"<< currentRenderGun.getPos().y<< std::endl;
		//std::cout << "z:"<<currentRenderGun.getPos().z<<std::endl;
			bullets.push(currentRenderGun);
	}
}



void Bullet::bindingBullet(ShaderFunc& shaderID)
{
	readTriangleObj("obj_bullet.obj", bulletVertexData, bulletTextureData, bulletNormalData);
	shaderID.InitBuffer(bulletVAO, bulletVertexVBO, bulletTextureVBO, bulletNormalVBO, bulletVertexData, bulletTextureData, bulletNormalData);
}

void Bullet::addBullet(glm::vec3 cameraPos, glm::vec3 dir, glm::vec3 angle)
{
	bullets.push(BulletInfo(dir + cameraPos, dir, angle));
}

void Bullet::moveBullets()
{
	for (int i = 0; i < bullets.size(); i++) {
		BulletInfo currentRenderGun = bullets.front();
		bullets.pop();
		currentRenderGun.movePos();
		bullets.push(currentRenderGun);
	}
}
void Bullet::collideBullet(glm::vec3 Enemypositon[])
{
	for (int i = 0; i < bullets.size(); i++) {
		BulletInfo currentRenderGun = bullets.front();
		bullets.pop();
		//renderBullet(shaderID, currentRenderGun.getPos(), currentRenderGun.getRotateAngle());
		//���࿡ �浹���� �ʾҴٸ� �Ǵ� �����Ÿ��� �ȵƴٸ� �ٽ� �ִ´� -> �����Ÿ��� dir���� ������ ���
		for (int i = 0; i < sizeof(Enemypositon); i++) {
			if (currentRenderGun.getDirUnit() <= 100)//�ʱ⿡�� 49�� ����
			std::cout << currentRenderGun.getPos().x;
			std::cout << currentRenderGun.getPos().x;
			std::cout << currentRenderGun.getPos().x;
			bullets.push(currentRenderGun);
		}
	
	}
}





