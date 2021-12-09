#include "BulletInfo.h"

int BulletInfo::getDirUnit()
{
	return dirUnit;
}

void BulletInfo::movePos()
{
	dirUnit++;
	pos += 1.5f * bulletDir;
}

glm::vec3 BulletInfo::getPos()
{
	return glm::vec3(pos);
}

glm::vec3 BulletInfo::getRotateAngle()
{
	return glm::vec3(rotateAngle);
}

glm::vec3 BulletInfo::getDir()
{
	return glm::vec3(bulletDir);
}
