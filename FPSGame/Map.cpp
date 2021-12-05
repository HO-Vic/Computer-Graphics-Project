#include "Map.h"
Map::Map() {
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution= glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//생성자

Map::Map(glm::vec3 Position,
	glm::vec3 Rotation,
	glm::vec3 Revolution,
	glm::vec3 Scale,
	glm::vec3 Color) :Position{ Position }, Rotation{ Rotation }, Revolution{ Revolution }, Scale{ Scale }, Color{ Color } {
};//기본값 생성

Map::Map(const Map& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Map::~Map()
{

};

glm::mat4 Map:: Getmatrix() {
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
glm::mat4 Map::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	return result;
};
void Map:: Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};

void Map:: Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Map::Change_Revoltion(float x, float y, float z){
	Revolution = glm::vec3(x, y, z);
};

void Map:: Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Map:: Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Map::GetColor() {
	return Color;
};

void Map::Apply_Parent(Map* Parent1) {
	Parent = Parent1;
};

float Map::Return_PositionX() {
	return Position.x;
};

float Map::Return_PositionZ() {
	return Position.z;
};
void Map::renderMap(ShaderFunc shaderID)
{
	glBindVertexArray(mapVAO);
	mapMatrix = glm::mat4(1.0f);
	
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE6);
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	mapMatrix = glm::translate(mapMatrix, Position);
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Rotation.x ), glm::vec3(1, 0, 0));
	mapMatrix = glm::rotate(mapMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	mapMatrix = glm::scale(mapMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 1);
	shaderID.setTransMatrix(mapMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 6);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, mapVertexData.size());
};
void Map::bindingMap(ShaderFunc& shaderID)
{
	readTriangleObj("obj_smallmap_2.obj", mapVertexData, mapTextureData, mapNormalData);
	shaderID.InitBuffer(mapVAO, mapVertexVBO, mapTextureVBO, mapNormalVBO, mapVertexData, mapTextureData, mapNormalData);
}
