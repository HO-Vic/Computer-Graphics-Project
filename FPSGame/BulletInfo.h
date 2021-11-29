#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class BulletInfo
{
private:
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec3 rotateAngle = glm::vec3(0, 0, 0);
	glm::vec3 bulletDir = glm::vec3(0, 0, 0);//-> 크기는 1또는 더 적게 해서 속도 맞춘다 -> dir곱한게 일정 이상이라면 pop
	int dirUnit = 0;
public:
	BulletInfo(glm::vec3 playerPos, glm::vec3 dir, glm::vec3 angle) : pos(playerPos), bulletDir(dir), rotateAngle(angle) {}
public:
	int getDirUnit();
	void movePos();
public:
	glm::vec3 getPos();
	glm::vec3 getRotateAngle();
	glm::vec3 getDir();
};

