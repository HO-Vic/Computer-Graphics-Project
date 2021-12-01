#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
class Enemy
{
protected:
	GLuint EnemyVAO;
	GLuint EnemyVertexVBO;
	GLuint EnemyNormalVBO;
	GLuint EnemyTextureVBO;
	std::vector<glm::vec3> EnemyVertexData;
	std::vector<glm::vec3> EnemyNormalData;
	std::vector<glm::vec2> EnemyTextureData;
	glm::mat4 EnemyMatrix;
	glm::vec3 Position;//��ġ
	glm::vec3 Translate;//��ġ
	glm::vec3 Rotation;//ȸ����
	glm::vec3 Revolution;//������
	glm::vec3 Scale{ 1 };//������
	glm::vec3 Color{ 1 };//����
	glm::mat4 result = glm::mat4(1.0f);
	Enemy* Parent{ nullptr };
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
	virtual void renderEnemy(ShaderFunc& shaderID);
	void  Apply_Parent(Enemy* Parent1);
	virtual void bindingEnemy(ShaderFunc& shaderID);
	//virtual void Apply_Parent(Enemy* Parent1);
	virtual float Return_PositionX();
	virtual float Return_PositionZ();

};
