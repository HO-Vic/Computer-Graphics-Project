#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include"filetobuf.h"
#include<vector>
#include"readObj.h"
#include<random>
class Core
{
private:
	static Core* coreInst;
private:
	GLuint fragmentShader;
	GLuint modelvertexShader;
	GLuint ShaderID;

	char* vertexSource;
	char* fragmentSource;

	int Wwidth = 800;
	int Wheight = 600;

	const std::string fileName[11]{

	};
	//camera move
	glm::vec3 cameraPos = glm::vec3(-1.5f, 2.0f, 2.0f);
public:
	Core();
	~Core();
public:
	static void setCoreInst();
	static Core* getCoreInst();
	static void destroyCore();
private:
	//shader func
	void makeVertexShader();
	void makeFragmentShader();
	void makeShaderID();
	void InitBuffer();



};

