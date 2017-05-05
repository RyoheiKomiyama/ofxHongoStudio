#version 410

uniform float alpha;

in vec4 colorVarying;
out vec4 outputColor;

void main() {
	vec4 c = colorVarying;
	c.a = alpha;
	outputColor = c;
}