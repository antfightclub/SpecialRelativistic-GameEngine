#pragma once

#include "Vector3.hpp"

namespace Math {

	class Vector4D {
	public:
		// ********** Constructors **********

		// All values zero if no args
		Vector4D() : t{ 0.0 }, x{ 0.0 }, y{ 0.0 }, z{ 0.0 } {};

		// Constructor with all doubles
		Vector4D(double t, double x, double y, double z) : t{ t }, x{ x }, y{ y }, z{ z } {};

		// Constructor with double and vector3 for spatial component
		Vector4D(double t, Vector3 v) : t{ t }, x{ v.getX() }, y{ v.getY() }, z{ v.getZ() } {};
		
		// Constructor with Vector3 for spatial component, time is zero
		Vector4D(Vector3 v) : t{ 0.0 }, x{ v.getX() }, y{ v.getY() }, z{ v.getZ() } {};
		
		// Constructor with doubles for spatial component, time is zero
		Vector4D(double x, double y, double z) : t{ 0.0 }, x{ x }, y{ y }, z{ z } {};


		// ********** String representation
		friend std::ostream& operator<<(std::ostream& os, const Vector4D& v);
		

		// ********** Getters & Setters **********
		double  getT()  const { return t; }
		double  getX()  const { return x; }
		double  getY()  const { return y; }
		double  getZ()  const { return z; }
		Vector3 get3D() const { return Vector3(x, y, z); }
		
		void setT(double val) { t = val; }
		void setX(double val) { x = val; }
		void setY(double val) { y = val; }
		void setZ(double val) { z = val; }


		// ********** Operator overloads **********
		/*
		BEST PRACTICE FROM LEARNCPP 21.1
		Operators that do not modify their operands (e.g. arithmetic operators) should generally return results by value
		Operators that modify their leftmost operand (e.g. pre-increment and any of the assignment operators) should generally return the leftmost operand by reference.
		*/
		//Compound assignment plus
		Vector4D& operator+=(const Vector4D& rhs);

		//Binary plus
		friend Vector4D operator+(Vector4D lhs, const Vector4D& rhs);

		// Compound assignment minus
		Vector4D& operator-=(const Vector4D& rhs);

		// Binary minus
		friend Vector4D operator-(Vector4D lhs, const Vector4D& rhs);

		// compount assignment multiply with double
		Vector4D& operator *=(const double& rhs);

		// Binary multiply (vec3 * double)
		friend Vector4D operator*(Vector4D lhs, const double& rhs);

		// Compound assignment division with double
		Vector4D& operator /=(const double& rhs);

		// Binary divide (vec3 / double)
		friend Vector4D operator/(Vector4D lhs, const double& rhs);

		Vector4D operator+() const;

		Vector4D operator-() const;
		


		// ********** 4D Vector math **********
		//length of spatial component
		double length();

		// Length squared of spatial component
		double length_squared();

		// distance in 3D between spatial components of self and other
		double distanceTo(Vector4D other);

		// distance squared in 3D between spatial components of self and other
		double distanceToSquared(Vector4D other);

		// Dot product of spatial component
		double dot(Vector4D other);

		// Get lorentz factor
		double getGamma();

		// Get lorentzian inner product
		double lorentzianInnerProduct(Vector4D other);

		// Get the lorentzian squared norm
		double lorentzianSquaredNorm();

		// Get the lorentzian squared norm to another vector
		double lorentzianSquaredNormTo(Vector4D other);
		
		//
		Vector3 getHat(double length = 1.0);

		//
		void hat(double length = 1.0);

		//
		Vector4D getNormalize(double length = 1.0);

		//
		void normalize(double length = 1.0);


		Vector4D getLinearAdd(Vector4D N, double s);

		Vector4D getDivPoint(Vector4D other, double s);

		//TODO: to glsl method, where components are {x, y, z, t} 




	private:
		double t;
		double x;
		double y;
		double z;
	};

}