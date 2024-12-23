
#include "first_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "relativity/math/Vector3.hpp"

// For testing relativity math:
int main() {

	double x = 1.0;
	double y = 2.0;
	double z = 3.0;

	double a = 10.0;

	auto vec1 = mve::Vector3::Vector3(x, y, z);
	auto vec2 = mve::Vector3::Vector3(10.0);
	auto vec3 = vec1 * a;
	
	std::cout << "vec1 = " << vec1 << '\n' << "a = " << a << '\n';
	std::cout << "vec1 * a = " << vec3 << '\n';

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