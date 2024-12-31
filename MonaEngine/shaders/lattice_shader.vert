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
	//vec4 positionWorld = push.modelMatrix  * vec4(position, 1.0);
	vec3 v = position.xyz - (latticeUbo.Xp + latticeUbo.Xo);
	vec4 vertex = /*latticeUbo.Lorentz * */ vec4(v.x, v.y, v.z, -length(v));//vec4(v, -length(v));
	vertex.w = 1.0;
	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);
	vec4 POS = MVP * (latticeUbo.Lorentz * vertex);
	//POS.w = 1.0;
	gl_Position = POS;//vec4(v, -length(v));//vec4(v, length(v));// * vertex;
	
	
	//float factor = max(0.0, min(1.0, (200.0/(POS.w*POS.w))));
	//vec4 col = vec4(color, 1.0);
	//col.a *= factor;
	fragColor = vec4(color, 0.75);
}

