// Fragment Shader: line.frag
#version 330 core
out vec4 FragColor;

uniform vec3 mcolor; // No default value here

void main()
{
    FragColor = vec4(mcolor, 1.0f);
}
