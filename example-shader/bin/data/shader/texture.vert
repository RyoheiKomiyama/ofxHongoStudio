#version 410

uniform mat4 modelToWorld;
uniform mat4 worldToCamera;
uniform mat4 cameraToView;
in vec4 position;
in vec2 texcoord;
out vec2 texCoordVarying;

void main()
{
	texCoordVarying = texcoord;
	gl_Position = cameraToView * worldToCamera * modelToWorld * position;
}