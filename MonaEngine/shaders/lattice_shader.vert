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
	vec3 xp = latticeUbo.Xp;
	vec3 xo = latticeUbo.Xo;

	//xp.x *= -1.0;
	//xp.y *= -1.0;
	//xp.z *= -1.0;
	
	//xo.x *= -1.0;
	//xo.y *= -1.0;
	//xo.z *= -1.0;
	
	


	//vec3 v = position - xp + xo;

	
	
	//vec3 v = vec3(
	//				position.x /* - xp.x + xo.x	*/,	
	//				position.z /* - xp.y + xo.y	*/,	
	//			  (-position.y)/* - xp.z + xo.z	*/	
	//);
	
	vec3 v = vec3(position.x, position.y, position.z);



	//mat4 L = latticeUbo.Lorentz;
	//vec4 col0 = L[0];
	//vec4 col1 = L[1];
	//vec4 col2 = L[2];
	//vec4 col3 = L[3];
	//
	//mat4 Lorentz = mat4(
	//	col0.x, col0.z, -col0.y, col0.w,
	//	col1.x, col1.z, -col1.y, col1.w,
	//	col2.x, col2.z, -col2.y, col2.w,
	//	col3.x, -col3.y, col3.z, col3.w
	//);

	//vec4 vertex = /*Lorentz*/  vec4(v, -length(vec3(v.x - xp.x, v.z - xp.y, v.y  -xp.z))) ;//vec4(v, -length(v));
	vec4 vertex = latticeUbo.Lorentz * vec4(v, -length(v));
	
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

