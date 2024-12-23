#pragma once

#include <iostream>

namespace Math {

	class Vector3 {
	public:
		// Constructors
		Vector3() : x(0.0), y(0.0), z(0.0) {};

		Vector3(double val) : x(val), y(val), z(val) {};

		Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
		
		// Printing values
		friend std::ostream& operator<<(std::ostream& os, const Vector3& v);


		// Operator overloads
		//Vector3& operator+(Vector3& const u) {  }
		//Vector3 operator+(Vector3 othr) { this->x = this->x + othr.x; this->y = this->y + othr.y; this->z = this->z + othr.z; }
		
		//Compound assignment plus
		Vector3& operator+=(const Vector3& rhs) {
			x = x + rhs.x; 
			y = y + rhs.y;
			z = z + rhs.z;
			return *this;
		}

		// Binary plus
		friend Vector3 operator+(Vector3 lhs, const Vector3& rhs) {
			lhs += rhs;
			return lhs;
		}

		// Compound assignment minus
		Vector3& operator-=(const Vector3& rhs) {
			x = x - rhs.x;
			y = y - rhs.y;
			z = z - rhs.z;
			return *this;
		}

		// Binary minus
		friend Vector3 operator-(Vector3 lhs, const Vector3& rhs) {
			lhs -= rhs;
			return lhs;
		}

		// compount assignment multiply with double
		Vector3& operator *=(const double& rhs) {
			x = x * rhs;
			y = y * rhs;
			z = z * rhs;
			return *this;
		}

		// Binary multiply (vec3 * double)
		friend Vector3 operator*(Vector3 lhs, const double& rhs) {
			lhs *= rhs;
			return lhs;
		}

		// Compound assignment division with double
		Vector3& operator /=(const double& rhs) {
			x = x / rhs;
			y = y / rhs;
			z = z / rhs;
			return *this;
		}
		
		// Binary divide (vec3 / double)
		friend Vector3 operator/(Vector3 lhs, const double& rhs) {
			lhs /= rhs;
			return lhs;
		}

		// Negative
		// FIXME: Not sure if friend or just Vector3& here.... this works, but modifies original!
		friend Vector3 operator-(Vector3& rhs) {
			rhs.x = -rhs.x;
			rhs.y = -rhs.y;
			rhs.z = -rhs.z;
			return rhs;
		}

		// Vector3 operations
		Vector3 copy();

		Vector3 getHat();

		void hat();

		Vector3 getNormalize();

		void normalize();

		double length();
		
		double lengthSquared();

		double distanceTo(Vector3 other);

		double dot(Vector3 other);

		Vector3 cross(Vector3 other);

	private:
		double x;
		double y;
		double z;
	};

	std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "Vector3{" << v.x << ", " << v.y << ", " << v.z << "}" << '\n';
		return os;
	}

}