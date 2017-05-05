#version 410

uniform float alpha;
uniform float elapsedTime;

in vec4 colorVarying;
out vec4 outputColor;

float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	float noise_r = rand(colorVarying.rg); // 0~1
	float noise_g = rand(colorVarying.gb); // 0~1
	float noise_b = rand(colorVarying.br); // 0~1
	float scaledTime_r = (1+sin(elapsedTime*3))/2.0; // 0~1
	float scaledTime_g = (1+sin(elapsedTime*2))/2.0; // 0~1
	float scaledTime_b = (1+sin(elapsedTime*1))/2.0; // 0~1
	vec3 color_noise = vec3(scaledTime_r, scaledTime_g, scaledTime_b)
						+ vec3(noise_r, noise_g, noise_b);
	vec4 c = colorVarying;
	c.rgb = (c.rgb + color_noise)/3.0;
	c.a = alpha;
	outputColor = c;
}