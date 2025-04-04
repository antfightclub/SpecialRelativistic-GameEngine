#version 450

layout (location = 0) in vec4 fragColor;

layout (location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	vec4 ambientLightColor;
	vec4 observerPosition;
	vec4 PhiThetaEtaLambda;
} ubo;

layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
	mat4 Lorentz;
} latticeUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;

void main() {
	outColor = fragColor;
}