#pragma once
#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"readTriangleObj2.h"
#include"Enemy.h"
class Flyrobot :public Enemy
{
protected:
	GLuint FlyrobotVAO;
	GLuint FlyrobotVertexVBO;
	GLuint FlyrobotNormalVBO;
	GLuint FlyrobotTextureVBO;
	std::vector<glm::vec3> FlyrobotVertexData;
	std::vector<glm::vec3> FlyrobotNormalData;
	std::vector<glm::vec2> FlyrobotTextureData;
	glm::mat4 FlyrobotMatrix;
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
	void renderEnemy(ShaderFunc shaderID);

	void bindingEnemy(ShaderFunc& shaderID) override;
	void Apply_Parent(Flyrobot* Parent1);
	float Return_PositionX();
	float Return_PositionZ();

};
