#include"Robot.h"
Robot::Robot() {
	Translate = glm::vec3(0.0f, 0.0f, 0.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
	hp = 10;
};//생성자

Robot::Robot(const Robot& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
	hp = 10;
};

Robot::~Robot()
{

};

glm::mat4 Robot::Getmatrix() {
	return RobotMatrix;
};
glm::mat4 Robot::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
	return result;
};
void Robot::Change_Positon(float x, float y, float z) {
	Position = glm::vec3(x, y, z);
};



void Robot::Change_Rotation(float x, float y, float z) {
	Rotation = glm::vec3(x, y, z);
}
void Robot::Change_Revoltion(float x, float y, float z) {
	Revolution = glm::vec3(x, y, z);
};

void Robot::Change_Scale(float x, float y, float z) {
	Scale = glm::vec3(x, y, z);
}


void Robot::Change_Color(float x, float y, float z) {
	Color = glm::vec3(x, y, z);
};

glm::vec3 Robot::GetColor() {
	return Color;
};

void Robot::Apply_Parent(Robot* Parent1) {
	Parent = Parent1;
}

void Robot::robot(Robot* Body, Robot* Head, Robot* Larm, Robot* Rarm, Robot* Lleg, Robot* Rleg, ShaderFunc* shaderfunc)
{

};

float Robot::Return_PositionX() {
	return Position.x;
};

float Robot::Return_PositionZ() {
	return Position.z;
}
float Robot::Return_PositionY()
{
	return Position.y;
}
glm::vec3 Robot::get_Position()
{
	return Position + Translate + GotoZero;
}
//Robot* Robot::get_body()
//{
//	return Robotbody;
//}
;
void Robot::renderEnemy(ShaderFunc& shaderID, GLuint& RobotVAO, int size)
{
	glBindVertexArray(RobotVAO);
	RobotMatrix = glm::mat4(1.0f);
	if (Parent)
		RobotMatrix = Parent->Getmatrix();
	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE9);
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	RobotMatrix = glm::translate(RobotMatrix, Position);
	RobotMatrix = glm::translate(RobotMatrix, Translate);
	RobotMatrix = glm::translate(RobotMatrix, GotoZero);
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
	RobotMatrix = glm::rotate(RobotMatrix, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
	RobotMatrix = glm::scale(RobotMatrix, Scale);
	glm::mat4 normalMatrix = glm::mat4(1.0f);
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.y + Rotation.y), glm::vec3(0, 1, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.x + Rotation.x), glm::vec3(1, 0, 0));
	normalMatrix = glm::rotate(normalMatrix, glm::radians(Revolution.z + Rotation.z), glm::vec3(0, 0, 1));
	glm::vec3 color = glm::vec3(1, 1, 1);
	shaderID.setTransMatrix(RobotMatrix);
	shaderID.setNormalMatrix(normalMatrix);
	//shaderID.setColorVec(color);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 9);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 1);
	glDrawArrays(GL_TRIANGLES, 0, size);
}

void Robot::Trans_Positon(float x, float y, float z)
{
	Position = glm::vec3(x, y, z);
	//RobotMatrix = glm::translate(RobotMatrix, Translate);

}
void Robot::move_Positon(float x, float y, float z)
{
	Translate = glm::vec3(x, y, z);
}

bool Robot::MinusHp(int damage)
{
	hp -= damage;
	if (hp < 0) {
		return 1;
	}
	else {
		return 0;
	}
}

void Robot::Gotozero_Positon(float x, float y, float z)
{
	GotoZero = glm::vec3(x, y, z);
}

