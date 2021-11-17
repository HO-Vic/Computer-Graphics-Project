#version 330 core

layout(location = 0)in vec3 vertex;
layout(location = 1)in vec3 vertexNormal;
	
uniform mat4 modelTransform;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
uniform mat4 normalTransform;

out vec3 fragPos;
out vec3 normal;

void main()
{
	gl_Position = projectionTransform * viewTransform * modelTransform * vec4(vertex, 1.0f);
	fragPos = vec3(modelTransform * vec4(vertex, 1));
	normal = vec3(normalTransform * vec4(vertexNormal, 1));
}