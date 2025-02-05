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
	float g0 = ubo.BoostParams[0]; // g0
	float betax = ubo.BoostParams[1]; // g1
	float betay = ubo.BoostParams[2]; // g2
	float betaz = ubo.BoostParams[3]; // g3

	float vel = sqrt(betax*betax + betay*betay + betaz*betaz);

	float gamma = 1.0 / (sqrt(1 - (vel*vel)));
	
	

	mat4 Lorentz = mat4(
			1 + (gamma-1)*(betax*betax/vel*vel),   (gamma - 1)*(betax*betay/vel*vel),   (gamma - 1)*(betax*betay/vel*vel), gamma*(betax),
			  (gamma - 1)*(betax*betay/vel*vel), 1 + (gamma-1)*(betay*betay/vel*vel),   (gamma - 1)*(betay*betaz/vel*vel), gamma*(betay),
			  (gamma - 1)*(betax*betaz/vel*vel),   (gamma - 1)*(betay*betaz/vel*vel), 1 + (gamma-1)*(betaz*betaz/vel*vel), gamma*(betay),
									gamma*betax,						 gamma*betay,						  gamma*betaz,         gamma);


	
	vec3 v = vec3(position - latticeUbo.Xp + latticeUbo.Xo);
	
	vec4 vertex = -Lorentz * vec4(v, -length(v));
	vertex.w = 1.0;
	
	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);

	vec4 pos = MVP * vertex;

	gl_Position = pos;
	
	
	float factor = max(0.0, min(1.0, (40.0/(pos.w*pos.w))));
	vec4 col = vec4(color, 1.0);
	col.w *= factor;
	fragColor = col;
}

