#include "Gun.h"

void Gun::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos + glm::vec3(0.05f, -0.15f, -0.2f);
}

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
