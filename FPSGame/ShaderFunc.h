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
	GLuint shaderID;
	GLuint fragmentShader;
	GLuint modelvertexShader;
	char* vertexSource;
	char* fragmentSource;
public:
	void makeVertexShader();
	void makeFragmentShader();
	void makeShaderID();
	void InitBuffer(GLuint& VAO, GLuint& vertexVBO, GLuint& normalVBO, std::vector<glm::vec3>& modelVertex, std::vector<glm::vec3>& modelNormal);
public:
	GLuint getShaderID();
};

