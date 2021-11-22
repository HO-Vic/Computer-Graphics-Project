#include "Gun.h"

void Gun::setPos(glm::vec3 inPutpos)
{
	pos = inPutpos + glm::vec3(0,-0.2f,-0.2f);
}

void Gun::setRotate(glm::vec3 rotateA)
{
	rotateAngle = rotateA;
}

void Gun::setRevolu(glm::vec3 revoluA)
{
	revoluAngle = revoluA;
}
