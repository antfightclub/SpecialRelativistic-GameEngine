#include "Vector4D.hpp"

namespace Math {

	//length of spatial component
	double Vector4D::length() {
		return std::sqrt(x*x + y*y + z*z);
	}

	// Length squared of spatial component
	double Vector4D::length_squared() {
		return x * x + y * y + z * z;
	}

	// distance in 3D between spatial components of self and other
	double Vector4D::distanceTo(Vector4D other) {
		double a = x - other.getX();
		double b = y - other.getY();
		double c = z - other.getZ();
		return std::sqrt(a * a + b * b + c * c);
	}

	// distance squared in 3D between spatial components of self and other
	double Vector4D::distanceToSquared(Vector4D other) {
		double a = x - other.getX();
		double b = y - other.getY();
		double c = z - other.getZ();
		return a * a + b * b + c * c;
	}

	// Dot product of spatial component
	double Vector4D::dot(Vector4D other) {
		return x * other.getX() + y * other.getY() + z * other.getZ();
	}

	// Get lorentz factor
	double Vector4D::getGamma() {
		return std::sqrt(1.0 + x*x + y*y + z*z);
	}

	// Get lorentzian inner product
	double Vector4D::lorentzianInnerProduct(Vector4D other) {
		return x * other.getX() + y * other.getY() + z * other.getZ() - t * other.getT();
	}

	// Get the lorentzian squared norm
	double Vector4D::lorentzianSquaredNorm() {
		return x * x + y * y + z * z - t * t;
	}

	// Get the lorentzian squared norm to another vector
	double Vector4D::lorentzianSquaredNormTo(Vector4D other) {
		double a = t - other.t; // time component
		double b = x - other.x; // spatial x component
		double c = y - other.y; // spatial y component
		double d = z - other.z; // spatial z component
		return b * b + c * c + d * d - a * a;
	}

	//
	Vector3 Vector4D::getHat(double length) {
		double r = x * x + y * y + z * z;
		if (r > 0.0) {
			r = length / std::sqrt(r);
			return Vector3(x * r, y * r, z * r);
		}
		else {
			return Vector3(length, 0.0, 0.0);
		}
	}

	//
	void Vector4D::hat(double length) {
		double r = x * x + y * y + z * z;
		if (r > 0.0) {
			r = length / std::sqrt(r);
			x *= r;
			y *= r;
			z *= r;
		}
		else {
			x = length;
		}
	}

	//
	Vector4D Vector4D::getNormalize(double length) {
		double r = x * x + y * y + z * z;
		if (r > 0.0) {
			r = length / std::sqrt(r);
			return Vector4D(t, x * r, y * r, z * r);
		}
		else {
			return Vector4D(t, 0.0, 0.0, 0.0);
		}
	}

	//
	void Vector4D::normalize(double length) {
		double r = x * x + y * y + z * z;
		if (r > 0.0) {
			r = length / std::sqrt(r);
			x *= r;
			y *= r;
			z *= r;
		}
	}

	Vector4D Vector4D::getLinearAdd(Vector4D N, double s) {
		double tt = t + N.getT() * s;
		double xx = x + N.getX() * s;
		double yy = y + N.getY() * s;
		double zz = z + N.getZ() * s;
		return Vector4D(tt, xx, yy, zz);
	}

	// (1 - s) * self + s * other
	Vector4D Vector4D::getDivPoint(Vector4D other, double s) {
		double time = 1.0 - s; // Not sure if actually represents time. Named "time" instead of "t" to avoid local scope confusion.
		double tt = t * time + other.getT() * s;
		double xx = x * time + other.getX() * s;
		double yy = y * time + other.getY() * s;
		double zz = z * time + other.getZ() * s;
		return Vector4D(tt, xx, yy, zz);
	}


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

	Vector4D Vector4D::operator+() const {
		return *this;
	}

	Vector4D Vector4D::operator-() const {
		return  { -this->t, -this->x, -this->y, -this->z };
	}

	std::ostream& operator<<(std::ostream& os, const Vector4D& v) {
		os << "Vector4{" << v.t << ", " << v.x << ", " << v.y << ", " << v.z << "}" << '\n';
		return os;
	}
}