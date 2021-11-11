#version 330 core

in vec3 vertex;
uniform vec3 fragment;	
uniform mat4 Matrix;
uniform mat4 viewTransform;
uniform mat4 projectionTransform;
out vec3 outFrag;

void main()
{
	gl_Position = projectionTransform * viewTransform * Matrix * vec4(vertex, 1.0f);
	outFrag = fragment;
}