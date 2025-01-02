#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"
#include "Matrix44.hpp"

namespace Math {

	class Quaternion
	{
	public:
		// real component 1, imaginary components zero (corresponds to no rotation)
		Quaternion() : t{1.0}, x{0.0}, y{0.0}, z{0.0} {}


		// From doubles
		// If length is more than zero, normalize by length, otherwise initialize as zero rotation quat
		Quaternion(double t, double x, double y, double z) : t{0.0}, x{0.0}, y{0.0}, z{0.0} {
			double r;
			r = t * t + x * x + y * y + z * z;
			if (r > 0.0) {
				r = 1.0 / std::sqrt(r);
				this->t = t * r;
				this->x = x * r;
				this->y = y * r;
				this->z = z * r;
			}
			else {
				this->t = 1.0;
				this->x = 0.0;
				this->y = 0.0;
				this->z = 0.0;
			}
		}

		//// NOT axis!
		//Quaternion(double t, Vector3 v) : t{ 0.0 }, x{ 0.0 }, y{ 0.0 }, z{ 0.0 } {
		//	double r;
		//	r = t * t + v.getX() * v.getX() + v.getY() * v.getY() + v.getZ() * v.getZ();
		//	if (r > 0.0) {
		//		r = 1.0 / std::sqrt(r);
		//		this->t = t * r;
		//		this->x = v.getX() * r;
		//		this->y = v.getY() * r;
		//		this->z = v.getZ() * r;
		//	}
		//	else {
		//		this->t = 1.0;
		//		this->x = 0.0;
		//		this->y = 0.0;
		//		this->z = 0.0;
		//	}
		//}

		Quaternion(double x, double y, double z) : t{ 0.0 }, x{ 0.0 }, y{ 0.0 }, z{ 0.0 } {
			double r;
			r = x * x + y * y + z * z;
			if (r > 1.0) {
				r = 1.0 / std::sqrt(r);
				this->t = 0.0;
				this->x = x * r;
				this->y = y * r;
				this->z = z * r;
			}
			else if (r > 0.0) {
				this->t = 1.0 - std::sqrt(r);
				this->x = x;
				this->y = y;
				this->z = z;
			}
			else {
				this->t = 1.0;
				this->x = 0.0;
				this->y = 0.0;
				this->z = 0.0;
			}

		}

		// From axis
		Quaternion(double theta, Vector3 ax) {
			double c, s, x, y, z;
			c = std::cos(theta * 0.5);
			s = std::sin(theta * 0.5);
			x = ax.getZ();
			y = ax.getY();
			z = ax.getZ();
			this->t = c;
			this->x = x * s;
			this->y = y * s;
			this->z = z * s;
		};

		

		// From rotation matrix
		// Not doing this rn LOL
		Quaternion(Matrix44 R);


		// Multiplication (returns new matrix)
		friend Quaternion operator*(Quaternion lhs, const Quaternion& rhs);

		// Multiplication (overwrites self)
		Quaternion& operator*=(const Quaternion& rhs);


		Matrix44 getRotMat();

		Vector3 getRight_i();
		Vector3 getRight();
		Vector3 getUpward_i();
		Vector3 getUpward();
		Vector3 getForward_i();
		Vector3 getForward();

		void normalize();

		Quaternion getSphereP(Quaternion other, double t);

		double t;
		double x;
		double y;
		double z;
	//private:

	};
}