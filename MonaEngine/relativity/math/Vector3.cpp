#include "Vector3.hpp"


namespace Math {

	Vector3 Vector3::copy() {
		return Vector3(x, y, z);
	}

	/*Vector3 Vector3::getHat(double length) {
		double r = x * x + y * y + z * z;
		if (r >= 0.0) {
			r = length / std::sqrt(r);
			return Vector3(x * r, y * r, z * r);
		}
		else {
			return Vector3(length, 0.0, 0.0);
		}
	}*/



}
