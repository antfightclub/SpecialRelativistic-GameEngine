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
	vec4 PhiThetaEtaLambda;
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
	vec4 vertex = srUbo.L * vec4(v, -length(v));
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