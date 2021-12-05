#include "Particle.h"

glm::vec3 Particle::getPos()
{
	return glm::vec3(pos);
}

glm::vec3* Particle::getDir()
{
	return dir;
}

int Particle::getLife()
{
	return life;
}

void Particle::setLife()
{
	life+=1;
}
