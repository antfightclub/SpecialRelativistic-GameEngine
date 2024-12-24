#include "Matrix44.hpp"

namespace Math {



	std::ostream& operator<<(std::ostream& os, const Matrix44& mat) {
		os << "Matrix44{\n"
			<< mat.m00 << ", " << mat.m01 << ", " << mat.m02 << ", " << mat.m03 << ", \n"
			<< mat.m10 << ", " << mat.m11 << ", " << mat.m12 << ", " << mat.m13 << ", \n"
			<< mat.m20 << ", " << mat.m21 << ", " << mat.m22 << ", " << mat.m23 << ", \n"
			<< mat.m30 << ", " << mat.m31 << ", " << mat.m32 << ", " << mat.m33 << "} \n";
		return os;
	}
}