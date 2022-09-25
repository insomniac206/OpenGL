#version 440 core

out vec4 FragColor;
uniform vec4 ourColor;

void main()
{
	FragColor = vec4(ourColor.x, ourColor.y, ourColor.z, ourColor.w);
}