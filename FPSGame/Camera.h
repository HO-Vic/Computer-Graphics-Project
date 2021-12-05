#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include"ShaderFunc.h"
class Camera
{
private: 
	static Camera* cameraInst;
	static void setInst(glm::vec3 pos);
public:
	static Camera* getInst(glm::vec3 pos);
	static void destoy();
private:
	glm::vec3 pos = glm::vec3(0, 1.0f, 3.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 rotateAngle = glm::vec3(0.0f, 0.0f, 0.0f);
	float attackRotateX = 0.0f;
	bool isAttack = false;
private:
	glm::vec3 AT;
	glm::vec3 cameraDir;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
private:
	void setCameraRight();
	void setCameraUp();
public:
	Camera(glm::vec3 PlayerPos):pos(PlayerPos){
		AT = PlayerPos - glm::vec3(0, 0.9f, 2.0f);
		std::cout << AT.x << ' ' << AT.y << ' ' << AT.z << std::endl;
	}
public:
	const float walkRatio = 0.1f;
	const float runRatio = 0.3f;
public:
	void setCameraDir();
	void attackMotion(float recoil);
	void setStatusAttack(bool f, float recoil);
	void renderCamera(ShaderFunc& shaderID);
public:
	//move
	void moveFrontCamera();
	void moveBackCamera();
	void moveLeftCamera();
	void moveRightCamera();
	void moveUpCamera(float y);
	//run
	void runFrontCamera();
	void runBackCamera();
	void runLeftCamera();
	void runRightCamera();
	void moveRoateY(float Angle);
	void moveRoateX(float Angle);
	void setCameraAngleY(float Angle);
	void setCameraAngleX(float Angle);
	void setCameraAngleZ(float Angle);
	void initRecoilRotate();
	
public:
	glm::vec3 getPos();
	float getRotateX();
	glm::vec3 getDir();
};

