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
	vec4 ambientLightColor;
	vec4 observerPosition;
	vec4 BoostParams;
} ubo;

layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
	mat4 L;
} latticeUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;

void main() {
	float gamma = ubo.BoostParams[0]; // Lorentz factor
	float betax = ubo.BoostParams[1]; // g01 plane
	float betay = ubo.BoostParams[2]; // g02 plane
	float betaz = ubo.BoostParams[3]; // g03 plane

	float vel = sqrt(betax*betax + betay*betay + betaz*betaz);
	
	mat4 Bx = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, 1.0, 0.0, 0.0,
				   0.0, 0.0, gamma, gamma*betax,
				   0.0, 0.0, gamma*betax, gamma);

	mat4 By = mat4(gamma, 0.0, gamma*betay, 0.0,
				   0.0, 1.0, 0.0, 0.0,
				   gamma*betay, 0.0, gamma, 0.0,
				   0.0, 0.0, 0.0, 1.0);

	mat4 Bz = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, gamma, gamma*betaz, 0.0,
				   0.0, gamma*betaz, gamma, 0.0,
				   0.0, 0.0, 0.0, 1.0);

	mat4 Lorentz = Bx * By * Bz;

	
	vec3 v = vec3(position - latticeUbo.Xp + latticeUbo.Xo);
	
	vec4 vertex = Lorentz * vec4(v, -length(v));
	vertex.w = 1.0;
	
	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);

	vec4 pos = MVP * vertex;

	gl_Position = pos;
	
	
	float factor = max(0.0, min(1.0, (40.0/(pos.w*pos.w))));
	vec4 col = vec4(color, 1.0);
	col.w *= factor;
	fragColor = col;
}

