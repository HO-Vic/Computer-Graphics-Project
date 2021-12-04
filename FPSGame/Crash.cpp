#pragma once
#include"Crash.h"
#include"Camera.h"
void Crash(std::vector<glm::vec3> vertex, glm::vec3 objPosition ) {
	float BigTempX=0, SmallTempX=0, BigTempY=0, SmallTempY=0, BigTempZ=0, SmallTempZ=0;
	bool check = 1;
	int i = 0;
	while (check) {
		for ( i ; i < 6; i++) {
			if (vertex[i].x >= BigTempX) {
				BigTempX = vertex[i].x;
			}
			if (vertex[i].x <= SmallTempX) {
				SmallTempX = vertex[i].x;
			}
			if (vertex[i].y >= BigTempY) {
				BigTempY = vertex[i].y;
			}
			if (vertex[i].y <= SmallTempY) {
				SmallTempY = vertex[i].y;
			}
			if (vertex[i].z >= BigTempZ) {
				BigTempZ = vertex[i].z;
			}
			if (vertex[i].z <= SmallTempZ) {
				SmallTempZ = vertex[i].z;
			}
		}
		i += 6;
		//if (objPosition.x<BigTempX + 0.25 && objPosition.x > SmallTempX - 0.25 && objPosition.z<BigTempZ + 0.25 && objPosition.z > SmallTempZ - 0.25 && BigTempY - objPosition.y > 0.5) {//��ü�� �������� ���� �ö� ���� ������
		//	objPosition.x = 0;//�������� �������� �����
		//}
		if (objPosition.x<BigTempX && objPosition.x > SmallTempX && objPosition.z<BigTempZ && objPosition.z > SmallTempZ) {//��ü�� �������� ���� �ö� ���� ������
			if (BigTempY - objPosition.y <= 3 && BigTempY - objPosition.y >= -3.0) {
				Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->Changepos(BigTempY +1);
				//std::cout << "objPosition.x :" << objPosition.x<< "objPosition.y :" << objPosition.y<<"BigTempY" << BigTempY << std::endl;
				std::cout <<i<< "if" << vertex[i ].y << std::endl;
				check = 0;
			}
		}
		else {
			//std::cout << "else"<<BigTempY << std::endl;
			Camera::getInst(glm::vec3(0, 1.0f, 3.0f))->Changepos(BigTempY );
		}
		if (vertex.size() <= i) {
			std::cout <<i<< "else" << vertex[i-1].y << std::endl;
			check = 0;
		}
		
	}
}