
#include "first_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"
#include "relativity/math/Matrix44.hpp"

// For testing relativity math:
//int main() {
//
//	Math::Matrix44 mat1 = Math::Matrix44(2.0);
//	Math::Matrix44 mat2 = Math::Matrix44(3.0);
//	Math::Vector4D Vec4D = Math::Vector4D(5.0, 2.0, 4.0, 4.0);
//
//	Math::Matrix44 mat3 = mat1.Lorentz(Vec4D);
//
//	std::cout << mat3;
//
//
//	return EXIT_SUCCESS;
//}


// VULKAN APP MAIN:

int main() {
	mve::FirstApp app{};
	try {
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
	
}
