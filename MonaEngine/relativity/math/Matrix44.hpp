#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"

namespace Math {
	class Matrix44 {
	public:
		// ********** Constructors **********
		// identity matrix if no value given
		Matrix44() :
			m00{ 1.0 }, m01{ 0.0 }, m02{ 0.0 }, m03{ 0.0 },
			m10{ 0.0 }, m11{ 1.0 }, m12{ 0.0 }, m13{ 0.0 },
			m20{ 0.0 }, m21{ 0.0 }, m22{ 1.0 }, m23{ 0.0 },
			m30{ 0.0 }, m31{ 0.0 }, m32{ 0.0 }, m33{ 1.0 } {};

		// Diagnoal with value
		Matrix44(double diag) :
			m00{ diag }, m01{ 0.0 }, m02{ 0.0 },  m03{ 0.0 },
			m10{ 0.0 },  m11{ diag}, m12{ 0.0 },  m13{ 0.0 },
			m20{ 0.0 },  m21{ 0.0 }, m22{ diag }, m23{ 0.0 },
			m30{ 0.0 },  m31{ 0.0 }, m32{ 0.0 },  m33{ diag } {};

		// // ********** String representation **********
		friend std::ostream& operator<<(std::ostream& os, const Matrix44& mat);

		// ********** Getters and Setters **********




		// ********** Operator overloads **********

		// Multiplication (returns new matrix)
		friend Matrix44 operator*(Matrix44 lhs, const Matrix44& rhs);

		// Multiplication (overwrites self)
		Matrix44& operator*=(const Matrix44& rhs);


		
		// // ********** 4x4 Matrix operations **********
		// NOTE: A lot of these are w.r.t. Lorentz transformations, using these matrix operations precede
		// that the matrix is a Lorentz transformation matrix. See "Special Relativity in Games", Sogebu et al.
		
		// X rotation (angle in radians)
		Matrix44 xRotation(double angle);

		// y rotation (angle in radians)
		Matrix44 yRotation(double angle);

		// z rotation (angle in radians)
		Matrix44 zRotation(double angle);

		// Scale a matrix
		Matrix44 scale(double scale);

		// Returns the inverse of a Matrix44 that is a 3D rotation by transposing its 3D rotation part.
		Matrix44 getInverseRotation();

		// ... not sure!! TODO
		Vector3 rotate(Vector3& v);

		// TBD how to do
		// array? GetRotate()
		
		Vector3 getRotate();

		// Overvwrites v by self * v
		void transform(Vector4D& v);

		// TBD not sure how I'll handle returning stuff as lists of things
		// array getTransform(Vector4D)

		// TBD 
		// array? toGLSL();

		// Returns lorentz factor
		double getGamma(); 

		// Returns a lorentz transformation matrix
		Matrix44 Lorentz(Vector4D u);



	private:
		double m00;
		double m01;
		double m02;
		double m03;

		double m10;
		double m11;
		double m12;
		double m13;

		double m20;
		double m21;
		double m22;
		double m23;

		double m30;
		double m31;
		double m32;
		double m33;
	};
}