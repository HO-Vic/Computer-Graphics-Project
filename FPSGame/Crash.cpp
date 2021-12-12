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
	else if (objPosition.x >= -41 && objPosition.z <= 24 && objPosition.z >= 2) {
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
	else if (objPosition.x >= -38 && objPosition.x <= -35 && objPosition.z > -19 && objPosition.z <= -8) {
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
	else if (objPosition.x >= -38 && objPosition.x <= -35 && objPosition.z > -19 && objPosition.z <= -8) {
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
	else if (objPosition.z < -22 && objPosition.x<-23 && objPosition.x > -39 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -22 && objPosition.z < 22.5 && objPosition.x <= -42 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > 22 && objPosition.x<-22 && objPosition.x > -39 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -13.8 && objPosition.z < 0 && objPosition.x>32 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > 0 && objPosition.x < 32 && objPosition.x > 25 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > 0 && objPosition.z > 21 && objPosition.x < 25 && objPosition.x > 6 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > 21 && objPosition.x < 25 && objPosition.x > 6 && objPosition.y < 7) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > 32 && objPosition.x < 6) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -7.5 && objPosition.z < -1.2 && objPosition.x<-28 && objPosition.x > -32.3) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -7.5 && objPosition.z < -1.2 && objPosition.x<-28 && objPosition.x > -32.3) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -13 && objPosition.z < 30.4 && objPosition.x < -53.8) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z < -13 && objPosition.x > -53.8 && objPosition.x < -41.4 && y>10) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z < -13 && objPosition.x < -41.4 && y>10) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z < -18 && objPosition.x > -41 && objPosition.x < -20.4 && y>10) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else if (objPosition.z > -10 && objPosition.z < -8 && objPosition.x > -44.0 && objPosition.x <= -38.0 && y > 10) {
		Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->moveCamera(tempPosition);
	}
	else {
		tempPosition = objPosition;
	}
}

