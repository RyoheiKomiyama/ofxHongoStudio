#version 410

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
uniform float elapsedTime;
in vec4 position;
in vec3 inputColor;
out vec4 colorVarying;

float rand(vec2 co){
	return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main() {
	vec3 pos = position.xyz;
	vec3 noise = vec3(rand(pos.xy), rand(pos.yz), rand(pos.zx));
	float scaledTime = (1+sin(elapsedTime*5))/10.0;
	pos = pos + noise*scaledTime;
	gl_Position = cameraToView * worldToCamera * modelToWorld * vec4(pos, 1);
	colorVarying = vec4(inputColor, 1.0);
}