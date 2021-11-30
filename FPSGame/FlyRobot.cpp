#include"FlyRobot.h"
Flyrobot::Flyrobot() {
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
};//������

Flyrobot::Flyrobot(const Flyrobot& object) {//���� ������

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
};

Flyrobot::~Flyrobot()
{

};

glm::mat4 Flyrobot::Getmatrix() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getmatrix();
	result = glm::rotate(result, glm::radians(Revolution.x), glm::vec3(1.0, 0, 0));//����
	result = glm::rotate(result, glm::radians(Revolution.y), glm::vec3(0, 1.0, 0));//����
	result = glm::rotate(result, glm::radians(Revolution.z), glm::vec3(0, 0, 1.0));//����
	result = glm::translate(result, Position);//�̵�
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//����
	result = glm::scale(result, Scale);
	return result;
};
glm::mat4 Flyrobot::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//����
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//����
	return result;
};
void Flyrobot::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};

void Flyrobot::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Flyrobot::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Flyrobot::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Flyrobot::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Flyrobot::GetColor() {
	return Color;
};

void Flyrobot::Apply_Parent(Flyrobot* Parent1) {
	Parent = Parent1;
};

float Flyrobot::Return_PositionX() {
	return Position.x;
};

float Flyrobot::Return_PositionZ() {
	return Position.z;
};
void Flyrobot::renderEnemy(ShaderFunc shaderID)
{
	glBindVertexArray(FlyrobotVAO);
	FlyrobotMatrix = glm::mat4(1.0f);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE4);
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	FlyrobotMatrix = glm::translate(FlyrobotMatrix, Position);
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	FlyrobotMatrix = glm::scale(FlyrobotMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(1, 1, 1);
	shaderID.setTransMatrix(FlyrobotMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	//shaderID.setColorVec(color);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 4);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, FlyrobotVertexData.size());
};
void Flyrobot::bindingEnemy(ShaderFunc& shaderID)
{
	readTriangleObj("obj_Flyrobot_body.obj", FlyrobotVertexData, FlyrobotTextureData, FlyrobotNormalData);
	//�ӽ� �ؽ��� ��ü��
	GLuint textureVboTemp;
	shaderID.InitBuffer(FlyrobotVAO, FlyrobotVertexVBO, FlyrobotTextureVBO, FlyrobotNormalVBO, FlyrobotVertexData, FlyrobotTextureData, FlyrobotNormalData);
}
