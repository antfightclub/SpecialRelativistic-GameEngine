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
	vec4 PhiThetaEtaLambda;
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
	float phi    = ubo.PhiThetaEtaLambda[0];
	float theta  = ubo.PhiThetaEtaLambda[1];
	float eta    = ubo.PhiThetaEtaLambda[2];
	float lambda = ubo.PhiThetaEtaLambda[3];
	
	mat4 S1 = mat4(cos(theta), 0.0, sin(theta), 0.0,
				   0.0, 1.0, 0.0, 0.0,
				  -sin(theta), 0.0, cos(theta), 0.0,
				   0.0, 1.0, 0.0, 1.0);

	mat4 S2 = mat4(cos(theta), -sin(theta), 0.0, 0.0,
				   sin(theta),  cos(theta), 0.0, 0.0,
				   0.0,	0.0, 1.0, 0.0,
				   0.0, 0.0, 0.0, 1.0);

	mat4 S3 = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, cos(phi), -sin(phi), 0.0,
				   0.0, sin(phi),  cos(phi), 0.0,
				   0.0, 0.0, 0.0, 1.0);

	mat4 K1 = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, cosh(lambda), 0.0, sinh(lambda),
				   0.0, 0.0, 1.0, 0.0,
				   0.0, sinh(lambda), 0.0, cosh(lambda));

	mat4 K2 = mat4(1.0, 0.0, 0.0, 0.0,
				   0.0, 1.0, 0.0, 0.0,
				   0.0, 0.0, cosh(lambda), sinh(lambda),
				   0.0, 0.0, sinh(lambda), cosh(lambda));

	mat4 K3 = mat4(cosh(eta), 0.0, 0.0, sinh(eta),
				   0.0, 1.0, 0.0, 0.0,
				   0.0, 0.0, 1.0, 0.0,
				   sinh(eta), 0.0, 0.0, cosh(eta));

	mat4 spacelike = S1 * S2 * S3;
	mat4 timelike  = K1 * K2 * K3;
	mat4 Lorentz   = spacelike * timelike;
	
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

