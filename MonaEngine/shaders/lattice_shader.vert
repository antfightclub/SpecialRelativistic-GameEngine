#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec4 fragColor;

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	mat4 ambientLightColor;
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
	vec3 v = position - latticeUbo.Xp + latticeUbo.Xo;
	vec4 positionWorld = push.modelMatrix * vec4(v, 1.0);
	//vec4 vertex = latticeUbo.Lorentz * vec4(v, -length(v));
	//vertex.w = 1.0;
	gl_Position = ubo.projection * ubo.view * positionWorld;
	float factor = max(0.0, min(1.0, (200.0/(gl_Position.w*gl_Position.w))));
	vec4 col = vec4(color, 1.0*factor);
	fragColor = col;
}

