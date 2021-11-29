#include "Gun.h"

void Gun::setRevoluAngleX(float Angle)
{
	revoluAngle.x = Angle;
}

void Gun::setRevoluAngleY(float Angle)
{
	revoluAngle.y = Angle;
}

void Gun::setRevoluAngleZ(float Angle)
{
	revoluAngle.z = Angle;
}

void Gun::moveRevoluX(float Angle)
{
	revoluAngle.x += Angle;
}

void Gun::moveRevoluY(float Angle)
{
	revoluAngle.y += Angle;
}

void Gun::initRecoilRotate()
{
	motionRevolu = 0;
}

float Gun::getRecoil()
{
	return recoil;
}

glm::vec3 Gun::getAngles()
{
	return (glm::vec3(rotateAngle.x + defaultRotateAngleX, rotateAngle.y, rotateAngle.z) + glm::vec3(revoluAngle.x + motionRevolu, revoluAngle.y, revoluAngle.z));
}

glm::vec3 Gun::getPos()
{
	return glm::vec3(pos);
}
