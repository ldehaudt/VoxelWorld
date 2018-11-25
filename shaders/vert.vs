#version 400 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 coord;

out vec2 fragCoord;
out vec2 TexCoord;
out float dist;

uniform mat4 matrix;

void main()
{
	gl_Position = matrix * vec4(aPos, 1.0);
	fragCoord = coord;
	dist = gl_Position.z;
}