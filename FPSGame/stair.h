#pragma once
#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
#include"readTriangleObj.h"
#include"Map.h"
class Stair:public Map
{
protected:
	GLuint StairVAO;
	GLuint StairVertexVBO;
	GLuint StairNormalVBO;
	GLuint StairTextureVBO;
	std::vector<glm::vec3> StairVertexData;
	std::vector<glm::vec3> StairNormalData;
	std::vector<glm::vec2> StairTextureData;
	glm::mat4 StairMatrix;
	Stair* Parent{ nullptr };
public:
	Stair();
	Stair(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Revolution,
		glm::vec3 Scale,
		glm::vec3 Color);
	Stair(const Stair& object);
	~Stair();
	glm::mat4 Getmatrix();
	glm::mat4 Getnormal();
	glm::vec3 GetColor();
	void Change_Positon(float x, float y, float z);
	void Change_Rotation(float x, float y, float z);
	void Change_Revoltion(float x, float y, float z);
	void Change_Scale(float x, float y, float z);
	void Change_Color(float x, float y, float z);
	void renderMap(ShaderFunc shaderID);

	void bindingMap(ShaderFunc& shaderID) override;
	void Apply_Parent(Stair* Parent1);
	float Return_PositionX();
	float Return_PositionZ();

};

