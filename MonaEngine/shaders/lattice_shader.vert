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
	vec4 U;
} latticeUbo;

layout(push_constant) uniform Push {
	mat4 modelMatrix;
} push;

void main() {
	//vec4 positionWorld = push.modelMatrix  * vec4(position, 1.0);
	//vec3 xp = latticeUbo.Xp;
	//vec3 xo = latticeUbo.Xo;
	
	vec3 v = vec3(position.x, position.y, position.z);

	vec3 beta = vec3(0.5, 0.0, 0.0);
	float b2 = (beta.x*beta.x + beta.y*beta.y+beta.z*beta.z)+1E-12;
	float g = 1.0 / (sqrt(abs(1.0 - b2))+1E-12);
	float q = (g - 1.0) / b2;

	mat4 lorentzTransformation = mat4(
	        1.0+beta.x*beta.x*q ,   beta.x*beta.y*q ,   beta.x*beta.z*q , beta.x*g ,
            beta.y*beta.x*q , 1.0+beta.y*beta.y*q ,   beta.y*beta.z*q , beta.y*g ,
            beta.z*beta.x*q ,   beta.z*beta.y*q , 1.0+beta.z*beta.z*q , beta.z*g ,
            beta.x*g , beta.y*g , beta.z*g , g
	);



	//vec4 vertex = /*Lorentz*/  vec4(v, -length(vec3(v.x - xp.x, v.z - xp.y, v.y  -xp.z))) ;//vec4(v, -length(v));
	vec4 vertex = lorentzTransformation * vec4(v, -length(v));
	
	vertex.w = 1.0;
	//vertex.y *= -1.0;
	

	mat4 MVP = (ubo.projection * ubo.view * push.modelMatrix);
	vec4 POS = MVP * (vertex);
	//POS.w = 1.0;
	gl_Position = vec4(POS.x, POS.y, POS.z, POS.w);//vec4(v, -length(v));//vec4(v, length(v));// * vertex;
	
	
	//float factor = max(0.0, min(1.0, (200.0/(POS.w*POS.w))));
	//vec4 col = vec4(color, 1.0);
	//col.a *= factor;
	fragColor = vec4(color, 0.75);
}

