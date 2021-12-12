#pragma once
#include"Crash.h"
#include"Camera.h"
float y = 1;
float tempy = 1;
glm::vec3 tempPosition;
void Crash(glm::vec3 objPosition) {
	if (objPosition.x >= -19 && objPosition.x <= 0.25 && objPosition.z >= 24) {
		if (objPosition.x <= 0) {
			float x = 0;
			if (objPosition.x < 0) {
				x = -objPosition.x;
			}
			else {
				x = objPosition.x;
			}
			y = 1 + x / 19 * 12;
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
	else if (objPosition.x >= -44 && objPosition.z <= 24 && objPosition.z >= 2) {
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
void Crash2(glm::vec3 objPosition) {
	if (objPosition.x >= 17 && objPosition.x <= 21 && objPosition.z < -20 && objPosition.z >= -30) {
		if (objPosition.z <= 0) {
			float z = 0;
			if (objPosition.z < 0) {
				z = -objPosition.z;
			}
			else {
				z = objPosition.x;
			}
			y = 1 + (z - 20) / 10 * 7;
			//std::cout <<"x" << x << std::endl;
		//	std::cout <<"y" << y << std::endl;
			tempy = y;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else if (objPosition.x >= 21 && objPosition.z < -16) {
		y = 7.9;
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else if (objPosition.x >= 21 && objPosition.z > -13.5) {
		if (objPosition.y >= 1.1) {
			//	std::cout << y;
			y -= 0.8;
		}
		else {
			y = 1;
			//		std::cout << "x ÁÂÇ¥" << objPosition.x << "y ÁÂÇ¥" << objPosition.y << "z ÁÂÇ¥" << objPosition.z << std::endl;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}
	else if (objPosition.x <= 17 && objPosition.z > -50 && objPosition.z < -14 && objPosition.y < 8.5) {
		if (objPosition.y >= 1.1) {
			//	std::cout << y;
			y -= 0.8;
		}
		else {
			y = 1;
			//		std::cout << "x ÁÂÇ¥" << objPosition.x << "y ÁÂÇ¥" << objPosition.y << "z ÁÂÇ¥" << objPosition.z << std::endl;
		}
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveUpCamera(y);
	}

}
void Crash3(glm::vec3 objPosition) {
	if (objPosition.z < -14 && objPosition.x<12 && objPosition.x > -22) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	/*else if (objPosition.z > -1 && objPosition.x<10.5 && objPosition.x > -23.5) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}*/
	/*else if (objPosition.z > -1 && objPosition.z <13 &&objPosition.x<7.5 && objPosition.x > -23.5) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}*/
	else if (objPosition.z < -14 && objPosition.x > 21.0 && objPosition.x < 30.0 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else {
		tempPosition = objPosition;
	}
}

