#pragma once

#include "Vector3.hpp"
#include "Vector4D.hpp"
#include <glm.hpp>
#include <vector>

// LAYOUT: 
//				col0		col1		col2		col3
//	row0	|	m00		|	m01		|	m02		|	m03		|
//	row1	|	m10		|	m11		|	m12		|	m13		|
//	row2	|	m20		|	m21		|	m22		|	m23		|
//	row3	|	m30		|	m31		|	m32		|	m33		|
//
// With Vector3 
//				right   = row1
//				up      = row2
//				forward = row3



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

		Matrix44(double m00, double m01, double m02, double m03,
				 double m10, double m11, double m12, double m13,
				 double m20, double m21, double m22, double m23,
				 double m30, double m31, double m32, double m33) :
			m00{ m00 }, m01{ m01 }, m02{ m02 }, m03{ m03 },
			m10{ m10 }, m11{ m11 }, m12{ m12 }, m13{ m13 },
			m20{ m20 }, m21{ m21 }, m22{ m22 }, m23{ m23 },
			m30{ m30 }, m31{ m31 }, m32{ m32 }, m33{ m33 } {};

		// // ********** String representation **********
		friend std::ostream& operator<<(std::ostream& os, const Matrix44& mat);

		// ********** Getters and Setters **********

		Vector3 getRow1() const { return Vector3{ m11, m12, m13 }; }
		Vector3 getRow2() const { return Vector3{ m21, m22, m23 }; }
		Vector3 getRow3() const { return Vector3{ m31, m32, m33 }; }

		void setRow1(double val11, double val12, double val13) { 
			m11 = val11;
			m12 = val12;
			m13 = val13;
		}
		void setRow2(double val21, double val22, double val23) { 
			m21 = val21;
			m22 = val22;
			m23 = val23;
		}
		void setRow3(double val31, double val32, double val33) { 
			m31 = val31;
			m32 = val32;
			m33 = val33;
		}


		// ********** Operator overloads **********

		// Multiplication (returns new matrix)
		friend Matrix44 operator*(Matrix44 lhs, const Matrix44& rhs);

		// Multiplication (overwrites self)
		Matrix44& operator*=(const Matrix44& rhs);

		Matrix44 copy();
		
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

		// 
		void rotate(Vector3& v);

		// 
		Vector3 getRotate(Vector3 v);
		

		// Overvwrites v by self * v
		void transform(Vector4D& v);

		Vector4D getTransform(Vector4D& v);

		// TBD not sure how I'll handle returning stuff as lists of things
		// array getTransform(Vector4D)

		// This routine converts the 3D rotation part of self into the openGL format.
		// TODO: (VERIFY THAT THIS IS CORRECT!)
		glm::mat4 toOpenGL();

		// This routine converts self into the GLSL format.
		// (VERIFY THAT THIS IS CORRECT!)
		glm::mat4 toGLM();

		// Returns lorentz factor
		double getGamma(); 

		// Returns a lorentz transformation matrix
		static Matrix44 Lorentz(Vector4D u);

		// There is most definitely a much better way of doing this LOL
		// Matrix is indexed as such when returned as doubles
		//	m[ 0] = m00		m[ 1] = m01		m[ 2] = m02		m[ 3] = m03
		//  m[ 4] = m10		m[ 5] = m11		m[ 6] = m12		m[ 7] = m13
		//	m[ 8] = m20		m[ 9] = m21		m[10] = m22		m[11] = m23
		//	m[12] = m30		m[13] = m31		m[14] = m32		m[15] = m33
		std::vector<double> getDoubles();


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