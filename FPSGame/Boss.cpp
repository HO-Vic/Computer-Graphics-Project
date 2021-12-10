#include"Boss.h"
Boss::Boss() {
	Translate = glm::vec3(0.0f, 0.0f, 0.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//������

Boss::Boss(const Boss& object) {//���� ������

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Boss::~Boss()
{

};

glm::mat4 Boss::Getmatrix() {
	return BossMatrix;
};
glm::mat4 Boss::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//����
	return result;
};
void Boss::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};



void Boss::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Boss::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Boss::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Boss::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Boss::GetColor() {
	return Color;
};

void Boss::Apply_Parent(Boss* Parent1) {
	Parent = Parent1;
}

void Boss::boss( ShaderFunc* shaderfunc)
{
	///*Bossbody = Body;
	//Bosslarm = Larm;
	//Bossrarm = Rarm;
	//Bossspin = Spin;*/
	//Head->Apply_Parent(Body);
	//Larm->Apply_Parent(Body);
	//Rarm->Apply_Parent(Body);
	//Lleg->Apply_Parent(Body);
	//Rleg->Apply_Parent(Body);
	//Body->renderEnemy(*shaderfunc);
	//Larm->renderEnemy(*shaderfunc);
	//Rarm->renderEnemy(*shaderfunc);
	//Head->renderEnemy(*shaderfunc);
	//Lleg->renderEnemy(*shaderfunc);
	//Rleg->renderEnemy(*shaderfunc);
};

float Boss::Return_PositionX() {
	return Position.x;
};

float Boss::Return_PositionZ() {
	return Position.z;
}
float Boss::Return_PositionY()
{
	return Position.y;
}
glm::vec3 Boss::get_Position()
{
	return Position + Translate;
}
Boss* Boss::get_body()
{
	return Bossbody;
}
;
void Boss::renderEnemy(ShaderFunc& shaderID)
{
	glBindVertexArray(BossVAO);
	BossMatrix = glm::mat4(1.0f);
	if (Parent)
		BossMatrix = Parent->Getmatrix();
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE9);
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	BossMatrix = glm::translate(BossMatrix, Position);
	BossMatrix = glm::translate(BossMatrix, Translate);
	BossMatrix = glm::translate(BossMatrix, GotoZero);
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	BossMatrix = glm::rotate(BossMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	BossMatrix = glm::scale(BossMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(1, 1, 1);
	shaderID.setTransMatrix(BossMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	//shaderID.setColorVec(color);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 9);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, BossVertexData.size());
}

void Boss::Trans_Positon(float x, float y, float z)
{
	Translate = glm::vec3(x, y, z);
	//BossMatrix = glm::translate(BossMatrix, Translate);

}

void Boss::Gotozero_Positon(float x, float y, float z)
{
	GotoZero = glm::vec3(x, y, z);
}

void Boss::bindingEnemy(ShaderFunc& shaderID, string name)
{
	readTriangleObj(name, BossVertexData, BossTextureData, BossNormalData);
	shaderID.InitBuffer(BossVAO, BossVertexVBO, BossTextureVBO, BossNormalVBO, BossVertexData, BossTextureData, BossNormalData);
}