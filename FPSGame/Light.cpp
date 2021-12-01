#include "Light.h"

void Light::setLightRevoluAngle(float angle)
{
	lightRevoluAngle = angle;
}

void Light::modifyLightRevolutAngle(float angle)
{
	lightRevoluAngle = angle;
}

void Light::setLightPos(glm::vec3 Pos)
{
	lightPos = Pos;
	lightPos.y = 3.0f;
}

void Light::modifyLightPos(glm::vec3 Pos)
{
	lightPos = Pos;
}

void Light::renderLight(ShaderFunc& shaderID)
{	
	unsigned int lightPosLocation = glGetUniformLocation(shaderID.getShaderID(), "LightPos");
	glUniform3fv(lightPosLocation, 1, glm::value_ptr(lightPos));

	glm::mat4 lightTransMatrix = glm::mat4(1.0f);
	lightTransMatrix = glm::rotate(lightTransMatrix, glm::radians(lightRevoluAngle), glm::vec3(0, 1, 0));
	unsigned int lightTransLocation = glGetUniformLocation(shaderID.getShaderID(), "LightTransform");
	glUniformMatrix4fv(lightTransLocation, 1, GL_FALSE, glm::value_ptr(lightTransMatrix));

	unsigned int lightColorLocation = glGetUniformLocation(shaderID.getShaderID(), "LightColor");
	glUniform3fv(lightColorLocation, 1, glm::value_ptr(lightColor));
}
