#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
class Map
{
protected:
	GLuint mapVAO;
	GLuint mapVertexVBO;
	GLuint mapNormalVBO;
	GLuint mapTextureVBO;
	std::vector<glm::vec3> mapVertexData;
	std::vector<glm::vec3> mapNormalData;
	std::vector<glm::vec2> mapTextureData;
	glm::mat4 mapMatrix;
	glm::vec3 Position;//위치
	glm::vec3 Translate;//위치
	glm::vec3 Rotation;//회전값
	glm::vec3 Revolution;//공전값
	glm::vec3 Scale{ 1 };//스케일
	glm::vec3 Color{ 1 };//색깔
	glm::mat4 result = glm::mat4(1.0f);
	Map* Parent{ nullptr };
public:
	Map();
	Map(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Map(const Map& object);
	~Map();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	virtual void Change_Positon(float x, float y, float z);
	virtual void Change_Rotation(float x, float y, float z);
	virtual void Change_Revoltion(float x, float y, float z);
	virtual void Change_Scale(float x, float y, float z);
	virtual void Change_Color(float x, float y, float z);
	virtual void renderMap(ShaderFunc shaderID);
	void  Apply_Parent(Map* Parent1);
	virtual void bindingMap(ShaderFunc& shaderID);
	//virtual void Apply_Parent(Map* Parent1);
	virtual float Return_PositionX();
	virtual float Return_PositionZ();
	
};

