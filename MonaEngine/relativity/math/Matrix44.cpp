#include "Matrix44.hpp"



namespace Math {

	// Multiplication (returns new matrix)
	Matrix44 operator*(Matrix44 lhs, const Matrix44& rhs) {
		Matrix44 ret = Matrix44::Matrix44(0.0);

		ret.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
		ret.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
		ret.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
		ret.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;

		ret.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
		ret.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
		ret.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
		ret.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;

		ret.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
		ret.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
		ret.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
		ret.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;

		ret.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
		ret.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
		ret.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
		ret.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;

		return ret;
	}

	// Multiplication (overwrites lhs)
	Matrix44& Matrix44::operator*=(const Matrix44& rhs) {
		double m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;

		m00 = this->m00 * rhs.m00 + this->m01 * rhs.m10 + this->m02 * rhs.m20 + this->m03 * rhs.m30;
		m01 = this->m00 * rhs.m01 + this->m01 * rhs.m11 + this->m02 * rhs.m21 + this->m03 * rhs.m31;
		m02 = this->m00 * rhs.m02 + this->m01 * rhs.m12 + this->m02 * rhs.m22 + this->m03 * rhs.m32;
		m03 = this->m00 * rhs.m03 + this->m01 * rhs.m13 + this->m02 * rhs.m23 + this->m03 * rhs.m33;

		m10 = this->m10 * rhs.m00 + this->m11 * rhs.m10 + this->m12 * rhs.m20 + this->m13 * rhs.m30;
		m11 = this->m10 * rhs.m01 + this->m11 * rhs.m11 + this->m12 * rhs.m21 + this->m13 * rhs.m31;
		m12 = this->m10 * rhs.m02 + this->m11 * rhs.m12 + this->m12 * rhs.m22 + this->m13 * rhs.m32;
		m13 = this->m10 * rhs.m03 + this->m11 * rhs.m13 + this->m12 * rhs.m23 + this->m13 * rhs.m33;

		m20 = this->m20 * rhs.m00 + this->m21 * rhs.m10 + this->m22 * rhs.m20 + this->m23 * rhs.m30;
		m21 = this->m20 * rhs.m01 + this->m21 * rhs.m11 + this->m22 * rhs.m21 + this->m23 * rhs.m31;
		m22 = this->m20 * rhs.m02 + this->m21 * rhs.m12 + this->m22 * rhs.m22 + this->m23 * rhs.m32;
		m23 = this->m20 * rhs.m03 + this->m21 * rhs.m13 + this->m22 * rhs.m23 + this->m23 * rhs.m33;

		m30 = this->m30 * rhs.m00 + this->m31 * rhs.m10 + this->m32 * rhs.m20 + this->m33 * rhs.m30;
		m31 = this->m30 * rhs.m01 + this->m31 * rhs.m11 + this->m32 * rhs.m21 + this->m33 * rhs.m31;
		m32 = this->m30 * rhs.m02 + this->m31 * rhs.m12 + this->m32 * rhs.m22 + this->m33 * rhs.m32;
		m33 = this->m30 * rhs.m03 + this->m31 * rhs.m13 + this->m32 * rhs.m23 + this->m33 * rhs.m33;
		
		this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
		this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
		this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
		this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
		
		return *this;
	}


	// X rotation (angle in radians) FIXME: NOT ACCOUNTED FOR AXIS DIFFERENCES
	Matrix44 Matrix44::xRotation(double angle) {
		double cos_a = std::cos(angle);
		double sin_a = std::sin(angle);
		Matrix44 m = Matrix44(0.0);

		m.m00 = 1.0;	m.m01 = 0.0;	m.m02 =   0.0;		m.m03 =    0.0;
		m.m10 = 0.0;	m.m11 = 1.0;	m.m12 =   0.0;		m.m13 =    0.0;
		m.m20 = 0.0;	m.m21 = 0.0;	m.m22 = cos_a;		m.m23 = -sin_a;
		m.m30 = 0.0;	m.m31 = 0.0;	m.m32 = sin_a;		m.m33 =  cos_a;
		return m;
	}

	// y rotation (angle in radians) FIXME: NOT ACCOUNTED FOR AXIS DIFFERENCES
	Matrix44 Matrix44::yRotation(double angle) {
		double cos_a = std::cos(angle);
		double sin_a = std::sin(angle);
		Matrix44 m = Matrix44(0.0);

		m.m00 = 1.0;	m.m01 =    0.0;		m.m02 = 0.0;	m.m03 =   0.0;
		m.m10 = 0.0;	m.m11 =  cos_a;		m.m12 = 0.0;	m.m13 = sin_a;
		m.m20 = 0.0;	m.m21 =    0.0;		m.m22 = 1.0;	m.m23 =   0.0;
		m.m30 = 0.0;	m.m31 = -sin_a;		m.m32 = 0.0;	m.m33 = cos_a;
		return m;
	}

	// z rotation (angle in radians) FIXME: NOT ACCOUNTED FOR AXIS DIFFERENCES
	Matrix44 Matrix44::zRotation(double angle) {
		double cos_a = std::cos(angle);
		double sin_a = std::sin(angle);
		Matrix44 m = Matrix44(0.0);

		m.m00 = 1.0;	m.m01 =   0.0;		m.m02 =    0.0;		m.m03 = 0.0;
		m.m10 = 0.0;	m.m11 = cos_a;		m.m12 = -sin_a;		m.m13 = 0.0;
		m.m20 = 0.0;	m.m21 = sin_a;		m.m22 =  cos_a;		m.m23 = 0.0;
		m.m30 = 0.0;	m.m31 =   0.0;		m.m32 =    0.0;		m.m33 = 1.0;
		return m;
	}

	// Scale a matrix
	Matrix44 Matrix44::scale(double scale) {
		Matrix44 m = Matrix44(0.0);
		m.m00 = 1.0;	m.m01 = 0.0;		m.m02 = 0.0;		m.m03 = 0.0;
		m.m10 = 0.0;	m.m11 = scale;		m.m12 = 0.0;		m.m13 = 0.0;
		m.m20 = 0.0;	m.m21 = 0.0;		m.m22 = scale;		m.m23 = 0.0;
		m.m30 = 0.0;	m.m31 = 0.0;		m.m32 = 0.0;		m.m33 = scale;
	}



	// Returns the inverse of a Matrix44 that is a 3D rotation by transposing its 3D rotation part.
	Matrix44 Matrix44::getInverseRotation() {
		Matrix44 m = Matrix44(0.0);
		m.m00 = this->m00; m.m01 = this->m01; m.m02 = this->m02; m.m03 = this->m03;
		m.m10 = this->m10; m.m11 = this->m11; m.m12 = this->m21; m.m13 = this->m31;
		m.m20 = this->m20; m.m21 = this->m12; m.m22 = this->m22; m.m23 = this->m32;
		m.m30 = this->m30; m.m31 = this->m13; m.m32 = this->m23; m.m33 = this->m33;
		return m;
	}

	// Rotates self. Let M be the 3D rotation part of self. This routine overwrites v by M*v
	//Vector3 Matrix44::rotate(Vector3& v) {
	//	Vector3 vec = Vector3(0.0);
	//	double x, y, z;
	//	x = v.getX();
	//	y = v.getY();
	//	z = v.getZ();
	//}

	// Returns lorentz factor
	double Matrix44::getGamma() {
		return this->m00;
	}

	Matrix44 Matrix44::Lorentz(Vector4D u) {
		Matrix44 m = Matrix44(1.0);
		double x, y, z, x2, y2, z2, r, g, xy, yz, zx;
		x = u.getX();
		y = u.getY();
		z = u.getZ();
		x2 = x * x;
		y2 = y * y;
		z2 = z * z;
		r = x2 + y2 + z2;
		if (r > 0.0) {
			g = std::sqrt(1.0 + r); // Lorentz factor
			r = 1.0 / r;
			xy = (g - 1.0) * x * y * r;
			yz = (g - 1.0) * y * z * r;
			zx = (g - 1.0) * z * x * r;

			m.m00 =  g;		m.m01 = -x;						m.m02 = -y;						m.m03 = -z;
			m.m10 = -x;		m.m11 = (g * x2 + y2 + z2) * r; m.m12 = xy;						m.m13 = zx;
			m.m20 = -y;		m.m21 = xy;						m.m22 = (x2 + g * y2 + z2) * r; m.m23 = yz;
			m.m30 = -z;		m.m31 = zx;						m.m32 = yz;						m.m33 = (x2 + y2 + g * z2) * r;
			return m;
		}
		else {
			return m; // Return Identity matrix44 if r is zero
		}
	}


	std::ostream& operator<<(std::ostream& os, const Matrix44& mat) {
		os << "Matrix44{\n"
			<< mat.m00 << ", " << mat.m01 << ", " << mat.m02 << ", " << mat.m03 << ", \n"
			<< mat.m10 << ", " << mat.m11 << ", " << mat.m12 << ", " << mat.m13 << ", \n"
			<< mat.m20 << ", " << mat.m21 << ", " << mat.m22 << ", " << mat.m23 << ", \n"
			<< mat.m30 << ", " << mat.m31 << ", " << mat.m32 << ", " << mat.m33 << "} \n";
		return os;
	}
}