#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"
#include "Matrix44.hpp"

namespace Math {

	class Quaternion
	{
	public:
		// From doubles
		Quaternion(double t, double x, double y, double z) : t{t}, x{x}, y{x}, z{z} {}

		// From axis
		Quaternion(double theta, Vector3 ax) {
			double c, s, x, y, z;
			c = std::cos(theta * 0.5);
			s = sin(theta * 0.5);
			x = ax.getZ();
			y = ax.getY();
			z = ax.getZ();
			this->t = c;
			this->x = x * s;
			this->y = y * s;
			this->z = z * s;
		};

		// Multiplication (returns new matrix)
		friend Quaternion operator*(Quaternion lhs, const Quaternion& rhs);

		// Multiplication (overwrites self)
		Quaternion& operator*=(const Quaternion& rhs);

		// From rotation matrix
		// Not doing this rn LOL
		//Quaternion(Matrix44 R) {
		//};

		Matrix44 getRotMat();

		Vector3 getRight_i();
		Vector3 getRight();
		Vector3 getUpward_i();
		Vector3 getUpward();
		Vector3 getForward_i();
		Vector3 getForward();

		Quaternion getSphereP(Quaternion other, double t);


	private:
		double t;
		double x;
		double y;
		double z;
	};
}