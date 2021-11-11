#include "Camera.h"

void Camera::setCameraDir(glm::vec3 AT)
{
	cameraDir = glm::normalize(pos - AT);//n
}
