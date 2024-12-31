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
	vec4 Xp;
	vec3 Xo;
	mat4 Lorentz;
} latticeUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;

void main() {
	//vec4 positionWorld = push.modelMatrix  * vec4(position, 1.0);
	float vx = position.x - latticeUbo.Xp.x;// + latticeUbo.Xo.x;
	float vy = position.y - latticeUbo.Xp.y;// + latticeUbo.Xo.y;
	float vz = position.z - latticeUbo.Xp.z;// + latticeUbo.Xo.z;

	vec3 v = vec3(vx, vy, vz);
	mat4 L = latticeUbo.Lorentz;
	
	vec4 vertex = L* vec4(v.z, v.x, v.y, -length(v));//vec4(v, -length(v));
	vertex.w = 1.0;
	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);
	vec4 POS = MVP * (vertex);
	//POS.w = 1.0;
	gl_Position = POS;//vec4(v, -length(v));//vec4(v, length(v));// * vertex;

	
	
	//float factor = max(0.0, min(1.0, (200.0/(POS.w*POS.w))));
	//vec4 col = vec4(color, 1.0);
	//col.a *= factor;
	fragColor = vec4(color, 0.75);
}

