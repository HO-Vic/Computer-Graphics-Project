#pragma once
#include"include/glew.h"
#include"include/freeglut.h"
#include"include/glm/glm.hpp"
#include"include/glm/ext.hpp"
#include"include/glm/gtc/matrix_transform.hpp"
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
public:
	void InitBuffer(GLuint& VAO, GLuint& vertexVBO, GLuint& textureVBO, GLuint& normalVBO, std::vector<glm::vec3>& modelVertex, std::vector<glm::vec2>& modelTexture, std::vector<glm::vec3>& modelNormal);

	void setTransMatrix(glm::mat4& transMatrix);
	void setTransMatrixorigin(glm::mat4 transMatrix);
	void setColorVec(glm::vec3 colorVec);//임시 -> 텍스쳐 되면 삭제
	void setNormalMatrix(glm::mat4& normalMatrix);
	void setNormalMatrixorigin(glm::mat4 normalMatrix);
public:
	GLuint getShaderID();
};

