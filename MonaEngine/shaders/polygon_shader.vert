#version 450
// vec4 coor
// mat4 Lorentz
// mat4 Lorentz_p2e
// mat4 Rotate
// vec4 dX			dX = X-Xp (in background frame, calculated before shadercall)
// vec4 xp			player X in background frame

// https://github.com/sogebu/LSBattle/blob/fbde754c5aee3250e42ac3f9ab5a5e4a4379ce92/model/polygon.py

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec2 uv;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out float ratio;

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	mat4 L;
	vec4 ambientLightColor;
	vec4 observerPosition;
} ubo;


layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
} latticeUbo;

layout(set = 0, binding = 2) uniform SRUbo {
	mat4 L_o2p;
	mat4 L_p2o;
	mat4 Rotate;
	vec4 dX;
	vec4 xp;
} srUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;


void main() {


	vec4 xi = srUbo.Rotate * vec4(position, 1.0);
	xi.w = srUbo.xp.w - distance(srUbo.xp.xyz, xi.xyz);
	xi = srUbo.dX + srUbo.L_o2p * xi;
	xi.w = -length(xi.xyz);
	vec4 tmp = srUbo.L_p2o * xi;
	ratio = xi.w / tmp.w;
	xi.w = 1.0;

	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);

	gl_Position = MVP * xi;

	fragColor = vec4(color, 1.0);
}