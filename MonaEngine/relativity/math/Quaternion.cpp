#include "Quaternion.hpp"

namespace Math {

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
}