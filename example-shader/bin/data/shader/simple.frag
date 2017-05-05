#version 410

in vec4 colorVarying;
out vec4 outputColor;

void main() {
	vec4 c = colorVarying;
	outputColor = c;
}