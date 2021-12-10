#include "CrossHead.h"

void CrossHead::drawdotCrossHead(ShaderFunc& shaderID)
{
	glm::mat4 dotM = glm::mat4(1.0f);
	glBindVertexArray(dotVao);
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), -1);
	glUniform3f(glGetUniformLocation(shaderID.getShaderID(), "objColor"), 1, 0, 0);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 1);
}

void CrossHead::drawSniperCrossHead(ShaderFunc& shaderID)
{
	glBindVertexArray(sniperDotVao);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, GL_TEXTURE5);
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "isTexture"), 2);
	glm::mat4 dotM = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "viewTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "projectionTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	dotM = glm::translate(dotM, glm::vec3(0, 0, -1));
	dotM = glm::scale(dotM, glm::vec3(2, 2, 2));
	glUniformMatrix4fv(glGetUniformLocation(shaderID.getShaderID(), "modelTransform"), 1, GL_FALSE, glm::value_ptr(dotM));
	glUniform1i(glGetUniformLocation(shaderID.getShaderID(), "textureC"), 5);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void CrossHead::binding(ShaderFunc& shaderID)
{
	
	glm::vec3 pointDot = glm::vec3(0, 0, -0.5);
	glm::vec3 normalDot = glm::vec3(0, 0, 1);

	glUseProgram(shaderID.getShaderID());
	glGenVertexArrays(1, &dotVao);
	glBindVertexArray(dotVao);
	glGenBuffers(1, &dotVbo);
	glBindBuffer(GL_ARRAY_BUFFER, dotVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &pointDot, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(0);
	glGenBuffers(1, &dotNormalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, dotNormalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &normalDot, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(1);

	readTriangleObj("obj_plane.obj", sniperDotVertexData, sniperDotTextureData, sniperDotNormalData);
	shaderID.InitBuffer(sniperDotVao, sniperDotVbo, sniperDotTextureVbo, sniperDotNormalVbo, sniperDotVertexData, sniperDotTextureData, sniperDotNormalData);
}
