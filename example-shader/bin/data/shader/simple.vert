#version 410

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
in vec4 position;
in vec3 inputColor;
out vec4 colorVarying;

void main() {
	gl_Position = cameraToView * worldToCamera * modelToWorld * position;
	colorVarying = vec4(inputColor, 1.0);
}