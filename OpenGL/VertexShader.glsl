#version 440 core

layout (location = 0) in vec3 vertexPos;

void main()
{
	gl_Position = vec4(vertexPos.x, vertexPos.y, vertexPos.z, 1.0);
}