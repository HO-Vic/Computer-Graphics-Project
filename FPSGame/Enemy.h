#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
#include<string>
using namespace std;
class Enemy
{
protected:
	glm::mat4 EnemyMatrix;
	glm::vec3 Position;//위치
	glm::vec3 Translate;//위치
	glm::vec3 GotoZero;//위치
	glm::vec3 Rotation;//회전값
	glm::vec3 Revolution;//공전값
	glm::vec3 Scale{ 1 };//스케일
	glm::vec3 Color{ 1 };//색깔
	glm::mat4 result = glm::mat4(1.0f);
	Enemy* Parent{ nullptr };
	bool Crashcheck=0;
	int hp;
public:
	Enemy();
	Enemy(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Enemy(const Enemy& object);
	~Enemy();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	virtual void Change_Positon(float x, float y, float z);
	virtual void Change_Rotation(float x, float y, float z);
	virtual void Change_Revoltion(float x, float y, float z);
	virtual void Change_Scale(float x, float y, float z);
	virtual void Change_Color(float x, float y, float z);	
	void  Apply_Parent(Enemy* Parent1);
	//virtual void Apply_Parent(Enemy* Parent1);
	virtual float Return_PositionX();
	virtual float Return_PositionZ();
	virtual float Return_PositionY();
	virtual glm::vec3 get_Position();
	virtual Enemy* get_body();
};
