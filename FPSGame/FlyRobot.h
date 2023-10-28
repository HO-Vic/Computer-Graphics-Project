#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
#include"Enemy.h"
#include<string>

using namespace std;

class Flyrobot :public Enemy
{
protected:
	glm::mat4 FlyrobotMatrix;

	//glm::vec3 FlyrobotPosition;
	Flyrobot* Parent{ nullptr };
public:
	Flyrobot();
	Flyrobot(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Flyrobot(const Flyrobot& object);
	~Flyrobot();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	void Change_Positon(float x, float y, float z);
	void Change_Rotation(float x, float y, float z);
	void Change_Revoltion(float x, float y, float z);
	void Change_Scale(float x, float y, float z);
	void Change_Color(float x, float y, float z);
	void renderEnemy(ShaderFunc& shaderID, GLuint& FlyrobotVAO, int size);
	void Trans_Positon(float x, float y, float z);
	void move_Positon(float x, float y, float z);
	void Gotozero_Positon(float x, float y, float z);
	void Attack_Player(glm::vec3 PlayerPosition, glm::vec3 RobotPosition, float time);
	void Apply_Parent(Flyrobot* Parent1);
	void FlyRobot(Flyrobot* Body, Flyrobot* Spin, Flyrobot* Larm, Flyrobot* Rarm, ShaderFunc* shaderfunc);
	float Return_PositionX()override;
	float Return_PositionZ()override;
	float Return_PositionY()override;
	glm::vec3 get_Position()override;
	bool Minushp(int gundamage);
	
	//	

};
