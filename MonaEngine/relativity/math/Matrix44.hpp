#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"

namespace Math {
	class Matrix44 {

	private:
		double m00;
		double m01;
		double m02;
		double m03;

		double m10;
		double m11;
		double m12;
		double m13;

		double m20;
		double m21;
		double m22;
		double m23;

		double m30;
		double m31;
		double m32;
		double m33;
	};
}