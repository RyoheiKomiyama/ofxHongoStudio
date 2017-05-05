#version 410

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
uniform float elapsedTime;
in vec4 position;
in vec3 inputColor;
out vec4 colorVarying;

void main() {
	vec3 pos = position.xyz;
	float scaledTime = 1+sin(elapsedTime*2);
	pos.y = pos.y*scaledTime;
	gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(pos, 1);
	colorVarying = vec4(inputColor, 1.0);
}