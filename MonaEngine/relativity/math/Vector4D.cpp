#include "Vector4D.hpp"

namespace Math {




	std::ostream& operator<<(std::ostream& os, const Vector4D& v) {
		os << "Vector4{" << v.t << ", " << v.x << ", " << v.y << ", " << v.z << "}" << '\n';
		return os;
	}
}