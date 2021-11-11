#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Map
{
private:
	glm::vec3 Position{ 0 };//��ġ
	glm::vec3 Translate{ 0 };//��ġ
	glm::vec3 Rotation{ 0 };//ȸ����
	glm::vec3 Scale{ 1 };//������
	glm::vec3 Color{ 1 };//����
	glm::mat4 result = glm::mat4(1.0f);
	Map* Parent{ nullptr };
public:
	Map() {
		Position = glm::vec3(0.0f, 0.0f, 0.0f);
		Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		Scale = glm::vec3(1.0f, 1.0f, 1.0f);
		Color = glm::vec3(1.0f, 1.0f, 1.0f);
		result = glm::mat4(1.0f);
	};//������
	Map(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Scale,
		glm::vec3 Color) {
		Position = Position;
		Rotation = Rotation;
		Scale = Scale;
		Color = Color;
	};//�⺻�� ����
	Map(const Map& object) {//���� ������

		Translate = object.Translate;
		Position = object.Position;
		Rotation = object.Rotation;
		Scale = object.Scale;
		Color = object.Color;
	};//������
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
	void Revolution(float x, float y, float z) {//���� 
		glm::mat4 Rx = glm::mat4(1.0f);//x�� ����
		glm::mat4 Ry = glm::mat4(1.0f);//y�� ����
		glm::mat4 Rz = glm::mat4(1.0f);//z�� ����
		result = glm::rotate(Rx, glm::radians(x), glm::vec3(x, 0.0, 0.0));//x�����
		result = glm::rotate(Ry, glm::radians(y), glm::vec3(0.0, y, 0.0));//y�����
		result = glm::rotate(Ry, glm::radians(z), glm::vec3(0.0, 0.0, z));//z�����
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

