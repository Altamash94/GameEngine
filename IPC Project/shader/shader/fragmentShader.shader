#version 330 core

out vec4 FragColor;
in vec2 Coord;

uniform sampler2D container;
uniform sampler2D face;

void main()
{
	vec4 tex1 = texture(container, Coord);
	vec4 tex2 = texture(face, Coord);
	FragColor = mix(tex1, tex2, 0.2f);
}