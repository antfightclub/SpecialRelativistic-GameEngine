#include "Vector4D.hpp"

namespace Math {

	//Compound assignment plus
	Vector4D& Vector4D::operator+=(const Vector4D& rhs) {
		t = t + rhs.t;
		x = x + rhs.x;
		y = y + rhs.y;
		z = z + rhs.z;
		return *this;
	}

	//Binary plus
	Vector4D operator+(Vector4D lhs, const Vector4D& rhs) {
		lhs += rhs;
		return lhs;
	}

	// Compound assignment minus
	Vector4D& Vector4D::operator-=(const Vector4D& rhs) {
		t = t - rhs.t;
		x = x - rhs.x;
		y = y - rhs.y;
		z = z - rhs.z;
		return *this;
	}

	// Binary minus
	Vector4D operator-(Vector4D lhs, const Vector4D& rhs) {
		lhs -= rhs;
		return lhs;
	}

	// compount assignment multiply with double
	Vector4D& Vector4D::operator *=(const double& rhs) {
		t = t * rhs;
		x = x * rhs;
		y = y * rhs;
		z = z * rhs;
		return *this;
	}

	// Binary multiply (vec3 * double)
	Vector4D operator*(Vector4D lhs, const double& rhs) {
		lhs *= rhs;
		return lhs;
	}

	// Compound assignment division with double
	Vector4D& Vector4D::operator /=(const double& rhs) {
		t = t / rhs;
		x = x / rhs;
		y = y / rhs;
		z = z / rhs;
		return *this;
	}

	// Binary divide (vec3 / double)
	Vector4D operator/(Vector4D lhs, const double& rhs) {
		lhs /= rhs;
		return lhs;
	}


	std::ostream& operator<<(std::ostream& os, const Vector4D& v) {
		os << "Vector4{" << v.t << ", " << v.x << ", " << v.y << ", " << v.z << "}" << '\n';
		return os;
	}
}