#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 OurColor;

uniform mat4 projection;//new
uniform mat4 view;//new
uniform mat4 model;//new

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);//new
	OurColor = aColor;
}