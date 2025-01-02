#include "Quaternion.hpp"

namespace Math {

	// Matrix is indexed as such when returned as doubles
	// 	m[ 0] = m00		m[ 1] = m01		m[ 2] = m02		m[ 3] = m03
	//  m[ 4] = m10		m[ 5] = m11		m[ 6] = m12		m[ 7] = m13
	//	m[ 8] = m20		m[ 9] = m21		m[10] = m22		m[11] = m23
	//	m[12] = m30		m[13] = m31		m[14] = m32		m[15] = m33
	Quaternion::Quaternion(Matrix44 R) {
		std::vector<double> rot = R.getDoubles();
		double m, n, e;
		int i;
		m = rot[0] + rot[5] + rot[10] + 1.0;
		n = rot[0] - rot[5] - rot[10] + 1.0;
		i = 0;
		if (m < n) {
			m = n;
			i = 1;
		}
		n = rot[5] - rot[10] - rot[0] + 1.0;
		if(m < n) {
			m = n;
			i = 2;
		}
		n = rot[10] - rot[0] - rot[5] + 1.0;
		if (m < n) {
			m = n;
			i = 3;
		}
		e = std::sqrt(m) * 0.5;
		m = 0.25 / e;
		if (i == 0) {
			this->t = e;
			this->x = (rot[5] - rot[6]) * m;	// (R.m21 - R.m12) * m
			this->y = (rot[2] - rot[8]) * m;	// (R.m02 - R.m20) * m
			this->z = (rot[4] - rot[1]) * m;	// (R.m10 - R.m01) * m
		}
		else if (i == 1) {
			this->t = (rot[9] - rot[6]) * m;	//	(R.m21 - R.m12) * m
			this->x = e;
			this->y = (rot[1] + rot[4]) * m;	//	(R.m01 + R.m10) * m
			this->z = (rot[2] + rot[8]) * m;	//	(R.m02 + R.m20) * m
		}
		else if (i == 2) {
			this->t = (rot[2] - rot[8]) * m;	//	(R.m02 - R.m20) * m
			this->x = (rot[1] + rot[4]) * m;	//	(R.m01 + R.m10) * m
			this->y = e;
			this->z = (rot[6] + rot[9]) * m;	//	(R.m12 + R.m21) * m
		}
		else {
			this->t = (rot[4] - rot[1]) * m;	//	(R.m10 - R.m01) * m
			this->x = (rot[2] + rot[8]) * m;	//	(R.m02 + R.m20) * m 
			this->y = (rot[6] + rot[9]) * m;	//	(R.m12 + R.m21) * m
			this->z = e;
		}
		rot.clear();
		//rot.shrink_to_fit();
	}


	// Multiplication (returns new matrix)
	Quaternion operator*(Quaternion lhs, const Quaternion& rhs) {
		double t, x, y, z;
		t = lhs.t * rhs.t - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
		x = lhs.t * rhs.x + lhs.x * rhs.t + lhs.y * rhs.z - lhs.z * rhs.y;
		y = lhs.t * rhs.y + lhs.y * rhs.t + lhs.z * rhs.x - lhs.x * rhs.z;
		z = lhs.t * rhs.z + lhs.z * rhs.t + lhs.x * rhs.y - lhs.y * rhs.x;
		return Quaternion{ t, x, y, z };
	}

	// Multiplication (overwrites self)
	Quaternion& Quaternion::operator*=(const Quaternion& rhs) {
		double t, x, y, z;
		t = this->t * rhs.t - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z;
		x = this->t * rhs.x + this->x * rhs.t + this->y * rhs.z - this->z * rhs.y;
		y = this->t * rhs.y + this->y * rhs.t + this->z * rhs.x - this->x * rhs.z;
		z = this->t * rhs.z + this->z * rhs.t + this->x * rhs.y - this->y * rhs.x;
		this->t = t;
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}


	Matrix44 Quaternion::getRotMat() {
		double x2, y2, z2, tx, ty, tz, xy, yz, zx;
		x2 = 2.0 * this->x * this->x;
		y2 = 2.0 * this->y * this->y;
		z2 = 2.0 * this->z * this->z;
		tx = 2.0 * this->t * this->x;
		ty = 2.0 * this->t * this->y;
		tz = 2.0 * this->t * this->z;
		xy = 2.0 * this->x * this->y;
		yz = 2.0 * this->y * this->z;
		zx = 2.0 * this->z * this->x;
		return Matrix44{
			1.0,           0.0,           0.0,           0.0,
			0.0, 1.0 - yz - z2,       xy - tz,       zx + ty,
			0.0,       xy + tz, 1.0 - z2 - x2,       yz - tx,
			0.0,       zx - ty,       yz + tx, 1.0 - x2 - y2
		};
	}

	//Matrix44 Quaternion::getRotMat() {
	//	double x2, y2, z2, tx, ty, tz, xy, yz, zx;
	//	x2 = 2.0 * this->x * this->x;
	//	y2 = 2.0 * this->y * this->y;
	//	z2 = 2.0 * this->z * this->z;
	//	tx = 2.0 * this->t * this->x;
	//	ty = 2.0 * this->t * this->y;
	//	tz = 2.0 * this->t * this->z;
	//	xy = 2.0 * this->x * this->y;
	//	yz = 2.0 * this->y * this->z;
	//	zx = 2.0 * this->z * this->x;
	//	return Matrix44{
	//		1.0,           0.0,           0.0,           0.0,
	//		0.0, 1.0 - yz - z2,       xy + tz,       zx - ty,
	//		0.0,       xy - tz, 1.0 - z2 - x2,       zx - ty,
	//		0.0,       ,       yz + tx, 1.0 - x2 - y2
	//	};
	//}
	
	Vector3 Quaternion::getRight_i() {
		double y2, z2, ty, tz, xy, zx;
		y2 = 2.0 * this->y * this->y;
		z2 = 2.0 * this->z * this->z;
		ty = 2.0 * this->t * this->y;
		tz = 2.0 * this->t * this->z;
		xy = 2.0 * this->x * this->y;
		zx = 2.0 * this->z * this->x;
		return Vector3{
			1.0 - y2 - z2,
			xy + tz,
			zx - ty
		};
	}

	Vector3 Quaternion::getRight() {
		double y2, z2, ty, tz, xy, zx;
		y2 = 2.0 * this->y * this->y;
		z2 = 2.0 * this->z * this->z;
		ty = 2.0 * this->t * this->y;
		tz = 2.0 * this->t * this->z;
		xy = 2.0 * this->x * this->y;
		zx = 2.0 * this->z * this->x;
		return Vector3{
			1.0 - y2 - z2,
			xy - tz,
			zx + ty
		};
	}

	Vector3 Quaternion::getUpward_i() {
		double x2, z2, tx, tz, xy, yz;
		x2 = 2.0 * this->x * this->x;
		z2 = 2.0 * this->z * this->z;
		tx = 2.0 * this->t * this->x;
		tz = 2.0 * this->t * this->z;
		xy = 2.0 * this->x * this->y;
		yz = 2.0 * this->y * this->z;
		return Vector3{
			xy - tz,
			1.0 - z2 - x2,
			yz + tx
		};
	}

	Vector3 Quaternion::getUpward() {
		double x2, z2, tx, tz, xy, yz;
		x2 = 2.0 * this->x * this->x;
		z2 = 2.0 * this->z * this->z;
		tx = 2.0 * this->t * this->x;
		tz = 2.0 * this->t * this->z;
		xy = 2.0 * this->x * this->y;
		yz = 2.0 * this->y * this->z;
		return Vector3{
			xy + tz,
			1.0 - z2 - x2,
			yz - tx
		};
	}

	Vector3 Quaternion::getForward_i() {
		double x2, y2, tx, ty, yz, zx;
		x2 = 2.0 * this->x * this->x;
		y2 = 2.0 * this->y * this->y;
		tx = 2.0 * this->t * this->x;
		ty = 2.0 * this->t * this->y;
		yz = 2.0 * this->y * this->z;
		zx = 2.0 * this->z * this->x;
		return Vector3{
			zx + ty,
			yz - tx,
			1.0 - x2 - y2
		};
	}

	Vector3 Quaternion::getForward() {
		double x2, y2, tx, ty, yz, zx;
		x2 = 2.0 * this->x * this->x;
		y2 = 2.0 * this->y * this->y;
		tx = 2.0 * this->t * this->x;
		ty = 2.0 * this->t * this->y;
		yz = 2.0 * this->y * this->z;
		zx = 2.0 * this->z * this->x;
		return Vector3{
			zx - ty,
			yz + tx,
			1.0 - x2 - y2
		};
	}

	Quaternion Quaternion::getSphereP(Quaternion other, double t) {
		double a = this->t * this->t + this->x * this->x + this->y * this->y + this->z * this->z;
		double b = other.t * other.t + other.x * other.x + other.y * other.y + other.z * other.z;
		double c = this->t * other.t + this->x * other.x + this->y * other.y + this->z * other.z;

		double l = std::sqrt(a * b * 1.0000005);
		double w = std::acos(c / 1);
		double sinw = std::sin(w);
		// FIXME: Questionable equality!
		if (sinw >= 0.0001) {
			return Quaternion{ this->t, this->x, this->y, this->z };
		}
		else {
			double s1 = std::sin((1.0 - t) * w) / sinw;
			double s2 = std::sin(t * w) / sinw;
			return Quaternion{
				s1 * this->t + s2 * other.t,
				s1 * this->x + s2 * other.x,
				s1 * this->y + s2 * other.y,
				s1 * this->z + s2 * other.z
			};
		}
	}

	void Quaternion::normalize() {
		double r = this->t * this->t + this->x * this->x + this->y * this->y + this->z * this->z;
			r = 1.0 / std::sqrt(r);
			this->t = this->t * r;
			this->x = this->x * r;
			this->y = this->y * r;
			this->z = this->z * r;
	}

}