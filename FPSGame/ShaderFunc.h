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
	void InitBuffer(GLuint& VAO, GLuint& vertexVBO, GLuint& textureVBO, GLuint& normalVBO, std::vector<glm::vec3>& modelVertex, std::vector<glm::vec3>& modelTexture, std::vector<glm::vec3>& modelNormal);
public:
	GLuint getShaderID();
public:
	void setTransformMatrix(glm::mat4& transMatrix);
	void setColorVec(glm::vec3 colorVec);//임시 -> 텍스쳐 되면 삭제
	void setNormalMatrix(glm::mat4& normalMatrix);
};

