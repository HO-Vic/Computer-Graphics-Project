#pragma once
#include"Crash.h"
#include"Camera.h"
void Crash(glm::vec3 objPosition ) {
	float y = 1;
	if (objPosition.x >= -19 &&objPosition.x<=0.25&& objPosition.z>=24) {
		if (objPosition.x <= 19) {
			float x = 0;
			if (objPosition.x < 0) {
				x = -objPosition.x;
			}
			else {
				x = objPosition.x;
			}
			y = 1 +   x/19*12;
			std::cout <<"x" << x << std::endl;
			std::cout <<"y" << y << std::endl;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else {
		std::cout << "x ÁÂÇ¥" << objPosition.x << "y ÁÂÇ¥" << objPosition.y << "z ÁÂÇ¥" << objPosition.z << std::endl;
	}
}