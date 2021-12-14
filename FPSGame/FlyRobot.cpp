#include"FlyRobot.h"
Flyrobot::Flyrobot() {
	Translate = glm::vec3(0.0f, 0.0f, 0.0f);
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Revolution = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	Color = glm::vec3(0.0f, 0.0f, 1.0f);
	result = glm::mat4(1.0f);
	hp = 15;
};//생성자

Flyrobot::Flyrobot(const Flyrobot& object) {//복사 생성자

	Translate = object.Translate;
	Position = object.Position;
	Rotation = object.Rotation;
	Scale = object.Scale;
	Color = object.Color;
	hp = 15;
};

Flyrobot::~Flyrobot()
{

}; 

glm::mat4 Flyrobot::Getmatrix() {
	return FlyrobotMatrix;
};
glm::mat4 Flyrobot::Getnormal() {
	result = glm::mat4(1.0f);
	if (Parent)
		result = Parent->Getnormal();
	result = glm::rotate(result, glm::radians(Rotation.x), glm::vec3(1.0, 0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.y), glm::vec3(0, 1.0, 0));//자전
	result = glm::rotate(result, glm::radians(Rotation.z), glm::vec3(0, 0, 1.0));//자전
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
}

//void Flyrobot::FlyRobot(Flyrobot* Body, Flyrobot* Spin, Flyrobot* Larm, Flyrobot* Rarm, ShaderFunc* shaderfunc)
//{
//	/*Flyrobotbody = Body;
//	Flyrobotlarm = Larm;
//	Flyrobotrarm = Rarm;
//	Flyrobotspin = Spin;*/
//	
//};

float Flyrobot::Return_PositionX() {
	return Position.x;
};

float Flyrobot::Return_PositionZ() {
	return Position.z;
}
float Flyrobot::Return_PositionY()
{
	return Position.y;
}
glm::vec3 Flyrobot::get_Position()
{
	return Position+Translate + GotoZero;
}

bool Flyrobot::Minushp(int gundamage)
{
	hp -= gundamage;
	if (hp < 0) {
		return 1;
	}
	else {
		return 0;
	}
}


void Flyrobot::renderEnemy(ShaderFunc& shaderID, GLuint& FlyrobotVAO, int size)
{
	glBindVertexArray(FlyrobotVAO);
	FlyrobotMatrix = glm::mat4(1.0f);
	if (Parent)
		FlyrobotMatrix = Parent->Getmatrix();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE4);
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.y), glm::vec3(0, 1, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.x), glm::vec3(1, 0, 0));
	FlyrobotMatrix = glm::rotate(FlyrobotMatrix, glm::radians(Revolution.z), glm::vec3(0, 0, 1));
	FlyrobotMatrix = glm::translate(FlyrobotMatrix, Position);
	FlyrobotMatrix = glm::translate(FlyrobotMatrix, Translate);
	FlyrobotMatrix = glm::translate(FlyrobotMatrix, GotoZero);
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
	glDrawArrays(GL_TRIANGLES, 0, size);
}

void Flyrobot::Trans_Positon(float x, float y, float z)
{
	Position = glm::vec3(x, y, z);
	//std::cout << Translate.x << ' ' << Translate.y <<' '<< Translate.z<<endl;
	//FlyrobotMatrix = glm::translate(FlyrobotMatrix, Translate);

}
void Flyrobot::move_Positon(float x, float y, float z)
{
	Translate = glm::vec3(x, y, z);
}
void Flyrobot::Gotozero_Positon(float x, float y, float z)
{
	GotoZero = glm::vec3(x, y, z);
}

void Flyrobot::Attack_Player(glm::vec3 PlayerPosition, glm::vec3 RobotPosition,float time)
{
	float x = 0,y=0,z=0;
	x = (PlayerPosition.x- RobotPosition.x)/10;
	y = (PlayerPosition.x - RobotPosition.y) / 10;
	z = (PlayerPosition.x - RobotPosition.z) / 10;

}


