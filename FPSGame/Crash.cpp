#pragma once
#include"Crash.h"
#include"Camera.h"
float y = 1;
float tempy = 1;
void Crash(glm::vec3 objPosition ) {
	if (objPosition.x >= -19 &&objPosition.x<=0.25&& objPosition.z>=24) {
		if (objPosition.x <= 0) {
			float x = 0;
			if (objPosition.x < 0) {
				x = -objPosition.x;
			}
			else {
				x = objPosition.x;
			}
			y = 1 +   x/19*12;
			//std::cout <<"x" << x << std::endl;
		//	std::cout <<"y" << y << std::endl;
			tempy = y;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else if (objPosition.x >= -48 && objPosition.x <= -44 && objPosition.z >= 24) {
		if (objPosition.x <= 0) {
			float x = 0;
			if (objPosition.x < 0) {
				x = -objPosition.x;
			}
			else {
				x = objPosition.x;
			}
			y = tempy + (x - 48) / 4;
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
		}
	}
	else if (objPosition.x >= -48 && objPosition.x <= -44 && objPosition.z >= 0) {
		tempy = y;
		if (objPosition.x <= 0) {
			float x = 0;
			if (objPosition.x < 0) {
				x = -objPosition.x;
			}
			else {
				x = objPosition.x;
			}
			y = tempy;
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
		}
	}
	else if (objPosition.x >= -44 && objPosition.z <= 24&&objPosition.z >= 2) {
		if (objPosition.y >= 1.1) {
		//	std::cout << y;
			y -= 0.8;
		}
		else {
	//		std::cout << "x ÁÂÇ¥" << objPosition.x << "y ÁÂÇ¥" << objPosition.y << "z ÁÂÇ¥" << objPosition.z << std::endl;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else {
	//	std::cout << "x ÁÂÇ¥" << objPosition.x << "y ÁÂÇ¥" << objPosition.y << "z ÁÂÇ¥" << objPosition.z << std::endl;
	}
}