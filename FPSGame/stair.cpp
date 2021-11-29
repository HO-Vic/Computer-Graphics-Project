#include "Stair.h"
Stair::Stair() {
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//생성자

Stair::Stair(const Stair& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Stair::~Stair()
{

};

glm::mat4 Stair::Getmatrix() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getmatrix();
	result = glm::rotate(result, glm::radians(Revolution.x), glm::vec3(1.0, 0, 0));//공전
	result = glm::rotate(result, glm::radians(Revolution.y), glm::vec3(0, 1.0, 0));//공전
	result = glm::rotate(result, glm::radians(Revolution.z), glm::vec3(0, 0, 1.0));//공전
	result = glm::translate(result, Position);//이동
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	result = glm::scale(result, Scale);
	return result;
};
glm::mat4 Stair::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	return result;
};
void Stair::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};

void Stair::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Stair::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Stair::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Stair::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Stair::GetColor() {
	return Color;
};

void Stair::Apply_Parent(Stair* Parent1) {
	Parent = Parent1;
};

float Stair::Return_PositionX() {
	return Position.x;
};

float Stair::Return_PositionZ() {
	return Position.z;
};
void Stair::renderMap(ShaderFunc shaderID)
{
	glBindVertexArray(StairVAO);
	StairMatrix = glm::mat4(1.0f);
	/*name->Change_Positon(0, 0, 0);
	name->Change_Rotation(0, 0, 0);
	name->Change_Scale(0, 0, 0);
	name->Change_Color(1, 0, 0);
	shaderID.setTransMatrixorigin(name->Getmatrix());
	shaderID.setNormalMatrixorigin(name->Getnormal());
	shaderID->setColorVec(name->GetColor());*/
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	StairMatrix = glm::translate(StairMatrix, Position);
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	StairMatrix = glm::rotate(StairMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	StairMatrix = glm::scale(StairMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 1);
	shaderID.setTransMatrix(StairMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glDrawArrays(GL_TRIANGLES, 0, StairVertexData.size());
};
void Stair::bindingMap(ShaderFunc& shaderID)
{
	readTriangleObj("obj_stair.obj", StairVertexData, StairTextureData,StairNormalData);
	//임시 텍스쳐 객체들
	GLuint textureVboTemp;
	shaderID.InitBuffer(StairVAO, StairVertexVBO, textureVboTemp, StairNormalVBO, StairVertexData, StairTextureData, StairNormalData);
}
