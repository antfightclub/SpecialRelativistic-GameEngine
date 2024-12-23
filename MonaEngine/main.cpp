
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
	
	double a = 2.0;

	Math::Vector3 vec1 = Math::Vector3(x, y, z);
	Math::Vector3 vec2 = vec1;
	vec2.hat();

	std::cout << "vec1 = " << vec1 << "vec2 = vec1; vec2.hat(); = " << vec2 << '\n';


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