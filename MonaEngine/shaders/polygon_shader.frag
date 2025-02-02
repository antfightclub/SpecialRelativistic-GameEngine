#version 450

layout (location = 0) in vec4 fragColor;
layout (location = 1) in float ratio;

layout (location = 0) out vec4 outColor;


layout(set = 0, binding = 0) uniform GlobalUbo {
	mat4 projection;
	mat4 view;
	mat4 invView;
	vec4 ambientLightColor;
	vec4 observerPosition;
} ubo;


layout(set = 0, binding = 1) uniform LatticeUbo {
	vec3 Xp;
	vec3 Xo;
	mat4 Lorentz;
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
	vec4 color = fragColor;
	
	color *= 255.0;
    float l = max(max(color.r, color.g), color.b);
    float Tr, Tg, Tb;
    if (l > 1) {
        color *= 255.0 / l;
        Tb = 1000.0 + 904.495*exp(0.00721929 * color.b);
        Tr = 6000.0 + 8.01879e20 * pow(max(color.r, 1.0), -7.507239275877164);
        if (color.b > 254.0) {
            Tg = 6502.86;
        } else {
            if (color.b / max(color.r, 1.0) > 0.98084) {
                Tg = 505.192 * exp(0.0100532 * color.g);
            } else {
                Tg = 6000.0 + 3.55446e34 * pow(max(color.g, 1), -13.24242861627803);
            }
        }
        Tr *= ratio;
        Tg *= ratio;
        Tb *= ratio;
        if (1905.0 > Tb) {
            color.b = 0.0;
        } else if (6700.0 < Tb) {
            color.b = 256.0;
        } else {
            color.b = -305.045 + 138.518 * log(0.01 * Tb - 10.0);
        }
        if (6689.0 > Tr) {
            color.r = 255.0;
        } else {
            color.r = 608.873 * pow(Tr - 6000.0, -0.133205);
        }
        if (506.0 > Tg) {
            color.g = 0.0;
        } else if (6502.86 > Tg) {
            color.g = -619.2 + 99.4708 * log(Tg);
        } else {
            color.g = 406.534 * pow(Tg - 6000.0, -0.0755148);
        }
        color *= l / 255.0;
    }
    outColor = vec4(color.r / 255.0, color.g / 255.0, color.b / 255.0, color.w / 255.0);

    

//	color *= 255.0;
//	float l = max(max(color.r, color.g), color.b);
//	float Tr, Tg, Tb;
//	if (l > 1) {
//		color *= 255.0 / l;
//		Tb = 1000.0 + 904.495*exp(0.00721929 * color.b);
//		Tr = 6000.0 + 8.01879e20 * pow(max(color.r, 1.0), -7.507239275877164);
//		if (color.b > 254.0) {
//			Tg = 6502.86;
//		} else {
//			if (color.b / max(color.r, 1.0) > 0.98084) {
//				Tg = 505.192 * exp(0.0100532 * color.g);
//			} else {
//				Tg = 6000.0 + 3.55446e34 * pow(max(color.g, 1), -13.24242861627803);
//			}
//		}
//		Tr *= ratio;
//		Tg *= ratio;
//		Tb *= ratio;
//		if (1905.0 > Tb) {
//			color.b = 0.0;
//		} else if(6700.0 < Tb) {
//			color.b = 255.0;
//		} else {
//			color.b = -305.045 + 138.518 * log(0.01 * Tb - 10.0);
//		}
//		if (6689.0 > Tr) {
//            color.r = 255.0;
//        } else {
//            color.r = 608.873 * pow(Tr - 6000.0, -0.133205);
//        }
//        if (506.0 > Tg) {
//            color.g = 0.0;
//        } else if (6502.86 > Tg) {
//            color.g = -619.2 + 99.4708 * log(Tg);
//        } else {
//            color.g = 406.534 * pow(Tg - 6000.0, -0.0755148);
//        }
//        color *= l / 255.0;
//	}
//	outColor = color / 255.0;
}