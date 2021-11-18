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

void ShaderFunc::InitBuffer(GLuint& VAO, GLuint& vertexVBO, GLuint& textureVBO, GLuint& normalVBO, std::vector<glm::vec3>& modelVertex, std::vector<glm::vec3>& modelTexture, std::vector<glm::vec3>& modelNormal)
{
	glUseProgram(shaderID);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, modelVertex.size() * sizeof(glm::vec3), &modelVertex[0], GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, modelNormal.size() * sizeof(glm::vec3), &modelNormal[0], GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);
}

void ShaderFunc::setTransMatrix(glm::mat4& transMatrix)
{
	unsigned int transMatrixLocation = glGetUniformLocation(shaderID, "modelTransform");
	glUniformMatrix4fv(transMatrixLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
}

void ShaderFunc::setColorVec(glm::vec3 colorVec)
{
	//юс╫ц
	unsigned int colorLocation = glGetUniformLocation(shaderID, "objColor");
	glUniform3fv(colorLocation, 1, glm::value_ptr(colorVec));
}

void ShaderFunc::setNormalMatrix(glm::mat4& normalMatrix)
{
	unsigned int normalMatrixLocation = glGetUniformLocation(shaderID, "normalTransform");
	glUniformMatrix4fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
}

GLuint ShaderFunc::getShaderID()
{
	return shaderID;
}

