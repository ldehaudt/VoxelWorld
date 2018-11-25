#version 400 core
out vec4 FragColor;

in float dist;
uniform float day;
in vec2 fragCoord;

uniform sampler2D tex0;

vec3 rgb2hsv(vec3 c)
{
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main()
{
	vec3 col = texture(tex0, fragCoord).xyz;
	col = rgb2hsv(col);

	vec3 coldusk = col;
	coldusk.y *= 0.7;
	coldusk.z *= coldusk.z;
	coldusk = hsv2rgb(coldusk);
	coldusk.x += 0.22;
	coldusk.y += 0.15;
	coldusk.z *= 1.5;
	coldusk = mix(coldusk, vec3(0.97, 0.85, 0.38),
	clamp((dist - 50) / 150, 0, 1));

	if (day > 0.0)
	{
		vec3 colday = col;

		colday.y *= 1.1;
		//colday.z *= 0.9;
		colday = hsv2rgb(colday);
		colday = mix(colday, vec3(0.908, 0.959, 0.975),
		clamp((dist - 50) / 150, 0, 1));

		FragColor = vec4(mix(colday, coldusk, clamp(1 - day, 0, 1)), 
		texture(tex0, fragCoord).a);
	}
	else
	{
		vec3 colnight = col;
		colnight.y *= 0.4;
		colnight.z *= colnight.z;
		colnight = hsv2rgb(colnight);
		colnight.z += 0.3;
		colnight.y += 0.1;
		colnight = mix(colnight, vec3(0.1, 0.24, 0.45),
		clamp((dist - 50) / 150, 0, 1));

		FragColor = vec4(mix(colnight, coldusk, clamp(1 + day, 0, 1)), 
		texture(tex0, fragCoord).a);
	}

}