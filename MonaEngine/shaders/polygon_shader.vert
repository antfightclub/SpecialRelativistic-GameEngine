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
	vec4 ambientLightColor;
	vec4 observerPosition;
	vec4 BoostParams;
} ubo;


layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
	mat4 L;
} latticeUbo;

layout(set = 0, binding = 2) uniform SRUbo {
	mat4 L;
	mat4 L_p2e;
	mat4 Rotate;
	vec4 dX;
	vec4 xp;
} srUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;


void main() {

	float g0 = ubo.BoostParams[0];
	float g1 = ubo.BoostParams[1];
	float g2 = ubo.BoostParams[2];
	float g3 = ubo.BoostParams[3];
	
	float x = g1;	
	float y = g2;
	float z = g3;
	float x2 = x*x;
	float y2 = y*y;
	float z2 = z*z;

	float r = x2 + y2 + z2;
	mat4 L = mat4(1.0);
	if (r >= 0.000001) {
		float g = sqrt(1.0 + r);

		r = 1.0 / r;

		float xy = (g-1.0) * x * y * r;
		float yz = (g-1.0) * y * z * r;
		float zx = (g-1.0) * z * x * r;

		L = mat4((g * x2 + y2 + z2) * r,					 xy,					 zx, -x,
									 xy, (x2 + g * y2 + z2) * r,					 yz, -y,
									 zx,					 yz, (x2 + y2 + g * z2) * r, -z,
									 -x,					 -y,					 -z,  g);
		

	} 

	vec4 xi = srUbo.Rotate * vec4(position, 1.0);
	xi.w = srUbo.xp.w - distance(srUbo.xp.xyz, xi.xyz);
	xi = srUbo.dX + L * xi;
	xi.w = -length(xi.xyz);
	vec4 tmp = srUbo.L_p2e * xi;
	ratio = xi.w / tmp.w;
	xi.w = 1.0;

	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);

	gl_Position = MVP * xi;

	fragColor = vec4(color, 1.0);
}