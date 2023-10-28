#pragma once
#pragma once
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

class Boss :public Enemy
{
protected:
	GLuint BossBodyVAO;
	GLuint BossBodyVertexVBO;
	GLuint BossBodyNormalVBO;
	GLuint BossBodyTextureVBO;
	std::vector<glm::vec3> BossBodyVertexData;
	std::vector<glm::vec3> BossBodyNormalData;
	std::vector<glm::vec2> BossBodyTextureData;

	GLuint BossMissileVAO;
	GLuint BossMissileVertexVBO;
	GLuint BossMissileNormalVBO;
	GLuint BossMissileTextureVBO;
	std::vector<glm::vec3> BossMissileVertexData;
	std::vector<glm::vec3> BossMissileNormalData;
	std::vector<glm::vec2> BossMissileTextureData;

	GLuint BossRedVAO;
	GLuint BossRedVertexVBO;
	GLuint BossRedNormalVBO;
	GLuint BossRedTextureVBO;
	std::vector<glm::vec3> BossRedVertexData;
	std::vector<glm::vec3> BossRedNormalData;
	std::vector<glm::vec2> BossRedTextureData;

	GLuint BossRocketVAO;
	GLuint BossRocketVertexVBO;
	GLuint BossRocketNormalVBO;
	GLuint BossRocketTextureVBO;
	std::vector<glm::vec3> BossRocketVertexData;
	std::vector<glm::vec3> BossRocketNormalData;
	std::vector<glm::vec2> BossRocketTextureData;

	glm::mat4 BossMatrix;

	float bossTransy = 100.0f;

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
	void renderBossComponent(ShaderFunc& shaderID, GLuint& vao, GLuint texture, int number, int size);
	void renderBoss(ShaderFunc& shaderID);
	void Trans_Positon(glm::vec3 a);
	void Gotozero_Positon(float x, float y, float z);
	void Apply_Parent(Boss* Parent1);
	void boss(ShaderFunc* shaderfunc);
	void missile(glm::vec3 missilepo, glm::vec3 missilere, glm::vec3 missilero);
	float Return_PositionX()override;
	float Return_PositionZ()override;
	float Return_PositionY()override;
	glm::vec3 get_Position()override;
	void bindingEnemys(ShaderFunc& shaderID);
	void decreaseBossYF();
	float getBossYF();
	bool minusHp(int damage);
	//	

}; 