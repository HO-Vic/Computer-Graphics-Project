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
#include<string>

using namespace std;

class Robot :public Enemy
{
protected:
	GLuint RobotVAO;
	GLuint RobotVertexVBO;
	GLuint RobotNormalVBO;
	GLuint RobotTextureVBO;
	std::vector<glm::vec3> RobotVertexData;
	std::vector<glm::vec3> RobotNormalData;
	std::vector<glm::vec2> RobotTextureData;
	glm::mat4 RobotMatrix;
	Robot* Robotbody;
	Robot* Robotlarm;
	Robot* Robotrarm;
	Robot* Robotspin;


	//glm::vec3 RobotPosition;
	Robot* Parent{ nullptr };
public:
	Robot();
	Robot(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Robot(const Robot& object);
	~Robot();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	void Change_Positon(float x, float y, float z);
	void Change_Rotation(float x, float y, float z);
	void Change_Revoltion(float x, float y, float z);
	void Change_Scale(float x, float y, float z);
	void Change_Color(float x, float y, float z);
	void renderEnemy(ShaderFunc& shaderID);
	void Trans_Positon(float x, float y, float z);
	void bindingEnemy(ShaderFunc& shaderID, string name) override;
	void Apply_Parent(Robot* Parent1);
	void robot(Robot* Body, Robot* head, Robot* Larm, Robot* Rarm, Robot* Lleg, Robot* Rleg, ShaderFunc* shaderfunc);
	float Return_PositionX()override;
	float Return_PositionZ()override;
	float Return_PositionY()override;
	glm::vec3 get_Position()override;
	Robot* get_body()override;

	//	

};
