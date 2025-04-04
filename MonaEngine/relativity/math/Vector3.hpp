#pragma once

#include <iostream>

namespace Math {

	class Vector3 {
	public:
		// ********** Constructors **********
		Vector3() : x(0.0), y(0.0), z(0.0) {};

		Vector3(double val) : x(val), y(val), z(val) {};

		Vector3(double x, double y, double z) : x(x), y(y), z(z) {};
		

		// ********** String representation **********
		friend std::ostream& operator<<(std::ostream& os, const Vector3& v);


		// ********** Getters & Setters **********
		double getX() const { return x; }
		double getY() const { return y; }
		double getZ() const { return z; }

		void setX(double val) { x = val; }
		void setY(double val) { y = val; }
		void setZ(double val) { z = val; }

		
		// ********** Operator overloads **********

		//BEST PRACTICE FROM LEARNCPP 21.1
		//Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value
		//Operators that modify their leftmost operand (e.g. pre-increment and any of the assignment operators) should generally return the leftmost operand by reference.

		//Compound assignment plus
		Vector3& operator+=(const Vector3& rhs);

		 //Binary plus
		friend Vector3 operator+(Vector3 lhs, const Vector3& rhs);

		// Compound assignment minus
		Vector3& operator-=(const Vector3& rhs);

		// Binary minus
		friend Vector3 operator-(Vector3 lhs, const Vector3& rhs);

		// compount assignment multiply with double
		Vector3& operator *=(const double& rhs);

		// Binary multiply (vec3 * double)
		friend Vector3 operator*(Vector3 lhs, const double& rhs);

		// Compound assignment division with double
		Vector3& operator /=(const double& rhs);
		
		// Binary divide (vec3 / double)
		friend Vector3 operator/(Vector3 lhs, const double& rhs);

		Vector3 operator+() const;

		Vector3 operator-() const;


		// ********** 3D vector math **********

		Vector3 getHat(double length = 1.0);

		void hat(double length = 1.0);

		Vector3 getNormalize(double length = 1.0);

		void normalize(double length = 1.0);

		double length();
		
		double lengthSquared();

		double distanceTo(Vector3 other);

		double distanceToSquared(Vector3 other);

		double dot(Vector3 other);

		Vector3 cross(Vector3 other);

	private:
		double x;
		double y;
		double z;
	};
}