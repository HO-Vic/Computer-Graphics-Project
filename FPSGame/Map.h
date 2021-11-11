#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Map
{
private:
	glm::vec3 Position{ 0 };//위치
	glm::vec3 Translate{ 0 };//위치
	glm::vec3 Rotation{ 0 };//회전값
	glm::vec3 Scale{ 1 };//스케일
	glm::vec3 Color{ 1 };//색깔
	glm::mat4 result = glm::mat4(1.0f);
	Map* Parent{ nullptr };
public:
	Map() {
		Position = glm::vec3(0.0f, 0.0f, 0.0f);
		Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		Color = glm::vec3(1.0f, 1.0f, 1.0f);
		result = glm::mat4(1.0f);
	};//생성자
	Map(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Scale,
		glm::vec3 Color) {
		Position = Position;
		Rotation = Rotation;
		Scale = Scale;
		Color = Color;
	};//기본값 생성
	Map(const Map& object) {//복사 생성자

		Translate = object.Translate;
		Position = object.Position;
		Rotation = object.Rotation;
		Scale = object.Scale;
		Color = object.Color;
	};//생성자
	Map() {
	};
	glm::mat4 Getmatrix() {
		result = glm::mat4(1.0f);
		if (Parent)
			result = Parent->Getmatrix();
		result = glm::translate(result, Position);
		result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));
		result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));
		result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));
		result = glm::scale(result, Scale);
		return result;
	};
	void Revolution(float x, float y, float z) {//공전 
		glm::mat4 Rx = glm::mat4(1.0f);//x축 자전
		glm::mat4 Ry = glm::mat4(1.0f);//y축 자전
		glm::mat4 Rz = glm::mat4(1.0f);//z축 자전
		result = glm::rotate(Rx, glm::radians(x), glm::vec3(x, 0.0, 0.0));//x축공전
		result = glm::rotate(Ry, glm::radians(y), glm::vec3(0.0, y, 0.0));//y축공전
		result = glm::rotate(Ry, glm::radians(z), glm::vec3(0.0, 0.0, z));//z축공전
		result = Rx * Ry * Rz;

	};
	void Change_Positon(float x, float y, float z) {
		Position = glm::vec3(x, y, z);
	};
	void Change_Rotation(float x, float y, float z) {
		Rotation = glm::vec3(x, y, z);
	};
	void Change_Scale(float x, float y, float z) {
		Scale = glm::vec3(x, y, z);
	};
	glm::vec3 Change_Color(float x, float y, float z) {
		Color = glm::vec3(x, y, z);
		return Color;
	};
	void Change_Translate(float x, float y, float z) {
		Translate = glm::vec3(x, y, z);
		result = glm::translate(result, Translate);
	};
	void Apply_Parent(Map* Parent1) {
		Parent = Parent1;
	}
	float Return_PositionX() {
		return Position.x;
	}
	float Return_PositionZ() {
		return Position.z;
	}
};

