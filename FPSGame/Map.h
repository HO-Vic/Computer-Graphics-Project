#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
class Map
{
private:
	glm::vec3 Position{ 0 };//위치
	glm::vec3 Translate{ 0 };//위치
	glm::vec3 Rotation{ 0 };//회전값
	glm::vec3 Scale{ 1 };//스케일
	glm::vec3 Color{ 1 };//색깔
	glm::mat4 result = glm::mat4(1.0f);
	Map* Parent{ nullptr };
public:
	Map();
	Map(glm::vec3 Position,
		glm::vec3 Rotation,
		glm::vec3 Scale,
		glm::vec3 Color);
	Map(const Map& object);
	glm::mat4 Getmatrix();
	void Revolution(float x, float y, float z);
	void Change_Positon(float x, float y, float z);
	void Change_Rotation(float x, float y, float z);
	void Change_Scale(float x, float y, float z);
	glm::vec3 Change_Color(float x, float y, float z);
	void Change_Translate(float x, float y, float z);
	void Apply_Parent(Map* Parent1);
	float Return_PositionX();
	float Return_PositionZ();
};

