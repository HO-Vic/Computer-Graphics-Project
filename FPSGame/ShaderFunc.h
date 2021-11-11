#pragma once
#include<gl/glew.h>
#include<gl/freeglut.h>
#include<glm/glm/glm.hpp>
#include<glm/glm/ext.hpp>
#include<glm/glm/gtc/matrix_transform.hpp>
#include<iostream>
#include"filetobuf.h"
class ShaderFunc
{
	GLuint ShaderID;
	GLuint fragmentShader;
	GLuint modelvertexShader;
	char* vertexSource;
	char* fragmentSource;
public:
	void makeVertexShader();
	void makeFragmentShader();
	void makeShaderID();
	void InitBuffer(GLuint VAO, GLuint VBO, std::vector<glm::vec4> modelVertex);
};

