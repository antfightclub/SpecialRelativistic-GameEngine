#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"

namespace Math {
	class Matrix44 {
	public:
		// identity matrix if no value given
		Matrix44() :
			m00{ 1.0 }, m01{ 0.0 }, m02{ 0.0 }, m03{ 0.0 },
			m10{ 0.0 }, m11{ 1.0 }, m12{ 0.0 }, m13{ 0.0 },
			m20{ 0.0 }, m21{ 0.0 }, m22{ 1.0 }, m23{ 0.0 },
			m30{ 0.0 }, m31{ 0.0 }, m32{ 0.0 }, m33{ 1.0 } {};

		// Diagnoal with value
		Matrix44(double diag) :
			m00{ diag }, m01{ 0.0 }, m02{ 0.0 },  m03{ 0.0 },
			m10{ 0.0 },  m11{ diag}, m12{ 0.0 },  m13{ 0.0 },
			m20{ 0.0 },  m21{ 0.0 }, m22{ diag }, m23{ 0.0 },
			m30{ 0.0 },  m31{ 0.0 }, m32{ 0.0 },  m33{ diag } {};

		// Printing
		friend std::ostream& operator<<(std::ostream& os, const Matrix44& mat);



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