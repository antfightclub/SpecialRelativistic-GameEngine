#version 450

const vec2 OFFSETS[6] = vec2[] (
	vec2(-1.0, -1.0),
	vec2(-1.0, 1.0),
	vec2(1.0, -1.0),
	vec2(1.0, -1.0),
	vec2(-1.0, 1.0),
	vec2(1.0, 1.0)
);

layout (location = 0) out vec2 fragOffset;
layout (location = 1) out vec3 fragColor;
layout (location = 2) out float ratio;

//struct PointLight {
//	vec4 position; // ignore w
//	vec4 color; // w is intensity
//};

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	vec4 ambientLightColor;
	vec4 observerPosition;
	vec4 BoostParams;
} ubo;


layout(set = 0, binding = 2) uniform SRUbo {
	mat4 L;
	mat4 L_p2e;
	mat4 Rotate;
	vec4 dX;
	vec4 xp;
} srUbo;

//layout(set = 0, binding = 3) uniform PointLightUbo {
//	PointLight pointLights[25];
//	vec4 observerPosition;
//	int numLights;
//} pointLightUbo;


layout(push_constant) uniform Push {
	vec4 position;
	vec4 color;
	float radius;
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

	fragOffset = OFFSETS[gl_VertexIndex];
	vec3 cameraRightWorld = {ubo.view[0][0], ubo.view[1][0], ubo.view[2][0]};
	vec3 cameraUpWorld = {ubo.view[0][1], ubo.view[1][1], ubo.view[2][1]};

	//vec4 adjustedCamRightWorld = -srUbo.L * vec4(cameraRightWorld, -length(cameraRightWorld));
	//vec4 adjustedCamUpWorld = -srUbo.L * vec4(cameraUpWorld, -length(cameraUpWorld));

	vec3 positionWorld = push.position.xyz
		+ push.radius * fragOffset.x * cameraRightWorld
		+ push.radius * fragOffset.y * cameraUpWorld;

	//gl_Position = ubo.projection * ubo.view * vec4(positionWorld-pointLightUbo.observerPosition.xyz, 1.0);

	vec3 v = vec3(positionWorld - ubo.observerPosition.xyz);
	vec4 vertex = L * vec4(v, -length(v));
	vertex.w = 1.0;

	vec4 xi = vec4(push.position.xyz, 1.0);
	xi.w = srUbo.xp.w - distance(srUbo.xp.xyz, xi.xyz);
	xi = srUbo.dX + srUbo.L * xi;
	xi.w = -length(xi.xyz);
	vec4 tmp = srUbo.L_p2e * xi;
	ratio = xi.w / tmp.w;
	
	fragColor = push.color.xyz;
	gl_Position = (ubo.projection * ubo.view) * vertex;
}