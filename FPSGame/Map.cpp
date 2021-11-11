#include "Map.h"
Map::Map() {
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(1.0f, 1.0f, 1.0f);
	result = glm::mat4(1.0f);
};//������
Map::Map(glm::vec3 Position,
	glm::vec3 Rotation,
	glm::vec3 Scale,
	glm::vec3 Color) {
	Position = Position;
	Rotation = Rotation;
	Scale = Scale;
	Color = Color;
};//�⺻�� ����
Map::Map(const Map& object) {//���� ������

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};//������

glm::mat4 Map:: Getmatrix() {//���� ���� �ʿ�
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
void Map::Revolution(float x, float y, float z) {//���� 
	glm::mat4 Rx = glm::mat4(1.0f);//x�� ����
	glm::mat4 Ry = glm::mat4(1.0f);//y�� ����
	glm::mat4 Rz = glm::mat4(1.0f);//z�� ����
	result = glm::rotate(Rx, glm::radians(x), glm::vec3(x, 0.0, 0.0));//x�����
	result = glm::rotate(Ry, glm::radians(y), glm::vec3(0.0, y, 0.0));//y�����
	result = glm::rotate(Ry, glm::radians(z), glm::vec3(0.0, 0.0, z));//z�����
	result = Rx * Ry * Rz;

};
void Map:: Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};
void Map:: Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
};
void Map:: Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
};
glm::vec3 Map:: Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
	return Color;
};
void Map:: Change_Translate(float x, float y, float z) {
	Translate = glm::vec3(x, y, z);
	result = glm::translate(result, Translate);
};
void Map:: Apply_Parent(Map* Parent1) {
	Parent = Parent1;
}
float Map:: Return_PositionX() {
	return Position.x;
}
float Map:: Return_PositionZ() {
	return Position.z;
}