#include "Projection.h"

void Projection::perspectriveProjection(ShaderFunc& shaderID, int Wwdith, int Wheight, float fovy)//원근 투영
{
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::translate(projection, glm::vec3(0, 0, -5.0f));
	projection = glm::perspective(glm::radians(fovy), (float)Wwdith / (float)Wheight, 0.1f, 100.0f);
	unsigned int projectionLocation = glGetUniformLocation(shaderID.getShaderID(), "projectionTransform");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

