#include "ShaderFunc.h"

void ShaderFunc::makeVertexShader()
{
	vertexSource = filetobuf("modelVertexShader.glsl");
	modelvertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(modelvertexShader, 1, &vertexSource, NULL);
	glCompileShader(modelvertexShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(modelvertexShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(modelvertexShader, 512, NULL, errorLog);
		std::cerr << "VERTEXSHADER ERROR: " << errorLog << std::endl;
	}
}

void ShaderFunc::makeFragmentShader()
{
	fragmentSource = filetobuf("fragmentShader.glsl");
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLint result;
	GLchar errorLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "FRAGMENT SHADER ERROR: " << errorLog << std::endl;
	}
}

void ShaderFunc::makeShaderID()
{
	makeVertexShader();
	makeFragmentShader();


	shaderID = glCreateProgram();

	glAttachShader(shaderID, modelvertexShader);
	glAttachShader(shaderID, fragmentShader);

	glLinkProgram(shaderID);

	glDeleteShader(modelvertexShader);
	glDeleteShader(fragmentShader);

	GLint result;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	GLchar errorLog[512];
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ShaderID Program ERROR: " << errorLog << std::endl;
	}
	glUseProgram(shaderID);
}

void ShaderFunc::InitBuffer(GLuint VAO, GLuint VBO, std::vector<glm::vec4> modelVertex)
{
	glUseProgram(shaderID);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, modelVertex.size() * sizeof(glm::vec4), &modelVertex[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec4), (void*)0);
	glEnableVertexAttribArray(0);
}

GLuint ShaderFunc::getShaderID()
{
	return shaderID;
}
