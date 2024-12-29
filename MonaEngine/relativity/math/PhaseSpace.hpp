#include "Vector4D.hpp"
#include "Matrix44.hpp"

namespace Math {
	class PhaseSpace {
	public:
		Vector4D X;
		Vector4D U;

		PhaseSpace(Vector4D X, Vector4D U) : X{X}, U{U} {}
		
		Vector4D getResist(double b);

		void transform(Vector4D accel, double ds);
	};
}