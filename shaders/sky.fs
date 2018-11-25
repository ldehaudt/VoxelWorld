#version 330 core
out vec4 FragColor;

in vec2 fragCoord;
uniform float day;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main()
{
	if (day > 0.0)
		FragColor = mix(texture(tex0, fragCoord),
		texture(tex1, fragCoord), clamp(1 - day, 0, 1));
	else
		FragColor = mix(texture(tex2, fragCoord), 
		texture(tex1, fragCoord), clamp(1 + day, 0, 1));
}
