
#include "first_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"

// For testing relativity math:
int main() {

	Math::Vector4D vec4D = Math::Vector4D{ 1.0, 5.0, 2.0, 3.0 };

	std::cout << vec4D << '\n';

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