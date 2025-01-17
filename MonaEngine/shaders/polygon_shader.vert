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

layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	mat4 ambientLightColor;
} ubo;

layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
	mat4 L;
	mat4 LL;
} latticeUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;


void main() {

vec3 v = vec3(position - latticeUbo.Xp);

	vec4 vertex = latticeUbo.L * vec4(v, -length(v));
	vertex.w = 1.0;
	
	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);

	vec4 pos = MVP * vertex;

	gl_Position = pos;
	
	//float factor = max(0.0, min(1.0, (40.0/(pos.w*pos.w))));
	vec4 col = vec4(color, 1.0);
	//col.w *= factor;
	fragColor = col;

}