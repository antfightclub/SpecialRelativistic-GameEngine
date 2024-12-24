
#include "first_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"
#include "relativity/math/Matrix44.hpp"

// For testing relativity math:
int main() {

	Math::Matrix44 mat = Math::Matrix44(1.0);

	std::cout << mat;


	return EXIT_SUCCESS;
}


// VULKAN APP MAIN:
/*
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
*/