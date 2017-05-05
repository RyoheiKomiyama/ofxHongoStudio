#version 410

uniform sampler2DRect tex0;
in vec2 texCoordVarying;
out vec4 fragColor;

void main() {
	vec4 tex = texture(tex0, texCoordVarying);
	fragColor = tex;
}