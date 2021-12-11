#pragma once
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

class Boss :public Enemy
{
protected:
	GLuint BossVAO;
	GLuint BossVertexVBO;
	GLuint BossNormalVBO;
	GLuint BossTextureVBO;
	std::vector<glm::vec3> BossVertexData;
	std::vector<glm::vec3> BossNormalData;
	std::vector<glm::vec2> BossTextureData;
	glm::mat4 BossMatrix;
	Boss* Bossbody;
	Boss* Bosslarm;
	Boss* Bossrarm;
	Boss* Bossspin;


	//glm::vec3 BossPosition;
	Boss* Parent{ nullptr };
public:
	Boss();
	Boss(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Boss(const Boss& object);
	~Boss();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	void Change_Positon(float x, float y, float z);
	void Change_Rotation(float x, float y, float z);
	void Change_Revoltion(float x, float y, float z);
	void Change_Scale(float x, float y, float z);
	void Change_Color(float x, float y, float z);
	void renderEnemy(ShaderFunc& shaderID, GLuint texture, int number);
	void Trans_Positon(float x, float y, float z);
	void Gotozero_Positon(float x, float y, float z);
	void bindingEnemy(ShaderFunc& shaderID, string name) override;
	void Apply_Parent(Boss* Parent1);
	void boss(ShaderFunc* shaderfunc);
	void missile(glm::vec3 missilepo, glm::vec3 missilere, glm::vec3 missilero);
	float Return_PositionX()override;
	float Return_PositionZ()override;
	float Return_PositionY()override;
	glm::vec3 get_Position()override;
	Boss* get_body()override;

	//	

};
