#include "Wall.h"
Wall::Wall() {
	Position = glm::vec3(0.0f, 0.0f, -50.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//생성자

Wall::Wall(const Wall& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Wall::~Wall()
{

};

glm::mat4 Wall::Getmatrix() {
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
glm::mat4 Wall::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	return result;
};
void Wall::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};

void Wall::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Wall::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Wall::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Wall::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Wall::GetColor() {
	return Color;
};

void Wall::Apply_Parent(Wall* Parent1) {
	Parent = Parent1;
};

float Wall::Return_PositionX() {
	return Position.x;
};

float Wall::Return_PositionZ() {
	return Position.z;
};
void Wall::renderMap(ShaderFunc shaderID)
{
	glBindVertexArray(WallVAO);
	WallMatrix = glm::mat4(1.0f);
	/*name->Change_Positon(0, 0, 0);
	name->Change_Rotation(0, 0, 0);
	name->Change_Scale(0, 0, 0);
	name->Change_Color(1, 0, 0);
	shaderID.setTransMatrixorigin(name->Getmatrix());
	shaderID.setNormalMatrixorigin(name->Getnormal());
	shaderID->setColorVec(name->GetColor());*/
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	WallMatrix = glm::translate(WallMatrix, Position);
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	WallMatrix = glm::rotate(WallMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	WallMatrix = glm::scale(WallMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(0, 0, 1);
	shaderID.setTransMatrix(WallMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	shaderID.setColorVec(color);
	glDrawArrays(GL_TRIANGLES, 0, WallVertexData.size());
};
void Wall::bindingMap(ShaderFunc& shaderID)
{
	readTriangleObj("obj_wall.obj", WallVertexData, WallNormalData);
	//임시 텍스쳐 객체들
	std::vector<glm::vec3> textureTemp;
	GLuint textureVboTemp;
	shaderID.InitBuffer(WallVAO, WallVertexVBO, textureVboTemp, WallNormalVBO, WallVertexData, textureTemp, WallNormalData);
}
