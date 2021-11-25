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
