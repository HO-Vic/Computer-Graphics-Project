#include "Enemy.h"
Enemy::Enemy() {
	Position = glm::vec3(0.0f, 0.0f, 10.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//생성자

Enemy::Enemy(glm::vec3 Position,
	glm::vec3 Rotation,
	glm::vec3 Revolution,
	glm::vec3 Scale,
	glm::vec3 Color) :Position{ Position }, Rotation{ Rotation }, Revolution{ Revolution }, Scale{ Scale }, Color{ Color } {
};//기본값 생성

Enemy::Enemy(const Enemy& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Enemy::~Enemy()
{

};

glm::mat4 Enemy::Getmatrix() {
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
glm::mat4 Enemy::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	return result;
};
void Enemy::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};

void Enemy::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Enemy::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Enemy::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Enemy::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Enemy::GetColor() {
	return Color;
};

void Enemy::Apply_Parent(Enemy* Parent1) {
	Parent = Parent1;
};

float Enemy::Return_PositionX() {
	return Position.x;
};

float Enemy::Return_PositionZ() {
	return Position.z;
}
float Enemy::Return_PositionY()
{
	return 0.0f;
}
glm::vec3 Enemy::get_Position()
{
	return glm::vec3();
}
Enemy* Enemy::get_body()
{
	return nullptr;
}
int Enemy::getHp()
{
	return hp;
}
;
//void Enemy::renderEnemy(ShaderFunc& shaderID)
//{
//	glBindVertexArray(EnemyVAO);
//	EnemyMatrix = glm::mat4(1.0f);
//	/*name->Change_Positon(0, 0, 0);
//	name->Change_Rotation(0, 0, 0);
//	name->Change_Scale(0, 0, 0);
//	name->Change_Color(1, 0, 0);
//	shaderID.setTransMatrixorigin(name->Getmatrix());
//	shaderID.setNormalMatrixorigin(name->Getnormal());
//	shaderID->setColorVec(name->GetColor());*/
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
//	EnemyMatrix = glm::translate(EnemyMatrix, Position);
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
//	EnemyMatrix = glm::rotate(EnemyMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
//	EnemyMatrix = glm::scale(EnemyMatrix, Scale);
//	glm::mat4 normalMatrix = glm::mat4(1.0f);
//	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
//	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
//	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
//	glm::vec3 color = glm::vec3(1, 0, 0);
//	shaderID.setTransMatrix(EnemyMatrix);
//	shaderID.setNormalMatrix(normalMatrix);
//	shaderID.setColorVec(color);
//	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 0);
//	glDrawArrays(GL_TRIANGLES, 0, EnemyVertexData.size());
//};
//void Enemy::bindingEnemy(ShaderFunc& shaderID, string name)
//{
//	readTriangleObj(name, EnemyVertexData, EnemyTextureData, EnemyNormalData);
//	shaderID.InitBuffer(EnemyVAO, EnemyVertexVBO, EnemyTextureVBO, EnemyNormalVBO, EnemyVertexData, EnemyTextureData, EnemyNormalData);
//}
