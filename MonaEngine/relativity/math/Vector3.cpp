#include "Vector3.hpp"


namespace Math {

	//Vector3 Vector3::copy() {
	//	return Vector3(x, y, z);
	//}

	Vector3 Vector3::getHat(double length) {
		double r = x * x + y * y + z * z;
		if (r >= 0.0) {
			r = length / std::sqrt(r);
			return Vector3(x * r, y * r, z * r);
		}
		else {
			return Vector3(length, 0.0, 0.0);
		}
	}

	void Vector3::hat(double length) {
		double r = x * x + y * y + z * z;
		if (r >= 0.0) {
			r = length / std::sqrt(r);
			x *= r;
			y *= r;
			z *= r;
		}
		else {
			x = length;
		}
	}




	//Compound assignment plus
	Vector3& Vector3::operator+=(const Vector3& rhs) {
		x = x + rhs.x;
		y = y + rhs.y;
		z = z + rhs.z;
		return *this;
	}

	//Binary plus
	Vector3 operator+(Vector3 lhs, const Vector3& rhs) {
		lhs += rhs;
		return lhs;
	}

	// Compound assignment minus
	Vector3& Vector3::operator-=(const Vector3& rhs) {
		x = x - rhs.x;
		y = y - rhs.y;
		z = z - rhs.z;
		return *this;
	}

	// Binary minus
	Vector3 operator-(Vector3 lhs, const Vector3& rhs) {
		lhs -= rhs;
		return lhs;
	}

	// compount assignment multiply with double
	Vector3& Vector3::operator *=(const double& rhs) {
		x = x * rhs;
		y = y * rhs;
		z = z * rhs;
		return *this;
	}

	// Binary multiply (vec3 * double)
	Vector3 operator*(Vector3 lhs, const double& rhs) {
		lhs *= rhs;
		return lhs;
	}

	// Compound assignment division with double
	Vector3& Vector3::operator /=(const double& rhs) {
		x = x / rhs;
		y = y / rhs;
		z = z / rhs;
		return *this;
	}

	// Binary divide (vec3 / double)
	Vector3 operator/(Vector3 lhs, const double& rhs) {
		lhs /= rhs;
		return lhs;
	}

	Vector3 Vector3::operator+() const {
		return *this;
	}

	Vector3 Vector3::operator-() const {
		return { -this->x, -this->y, -this->z };
	}

	std::ostream& operator<<(std::ostream& os, const Vector3& v) {
		os << "Vector3{" << v.x << ", " << v.y << ", " << v.z << "}" << '\n';
		return os;
	}

}
