#pragma once
#include"Crash.h"
void Crash(std::vector<glm::vec3> vertex, glm::vec3 objPosition ) {
	float BigTempX=0, SmallTempX=0, BigTempY=0, SmallTempY=0, BigTempZ=0, SmallTempZ=0;
	while (1) {
		for (int i = 0; i < 6; i++) {
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
		if (objPosition.x<BigTempX + 0.25 && objPosition.x > SmallTempX - 0.25 && objPosition.z<BigTempZ + 0.25 && objPosition.z > SmallTempZ - 0.25 && BigTempY - objPosition.y > 0.5) {//물체가 오비제이 위로 올라 갈수 있을때
			objPosition.x = 0;//포지션의 움직임이 멈춘다
		}
		else if (objPosition.x<BigTempX && objPosition.x > SmallTempX && objPosition.z<BigTempZ && objPosition.z > SmallTempZ&& BigTempZ - objPosition.y <= 0.5) {//물체가 오비제이 위로 올라 갈수 있을때
			objPosition.y = BigTempY;
		}
		
	}
}