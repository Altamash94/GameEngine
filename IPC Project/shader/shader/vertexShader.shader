#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aCoord;

out vec2 Coord;
uniform mat4 model, view, projection;

void main()
{
	Coord = aCoord;
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
};