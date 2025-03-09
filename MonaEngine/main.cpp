#define _CRT_SECURE_NO_WARNINGS
#include "relativity_app.hpp"

//std
#include <cstdlib>
#include <iostream>
#include <stdexcept>

int main() {
	//std::cout << "Main begun!" << '\n';

	mve::RelativityApp app{};
	//std::cout << "app initialized! " << '\n';
	try {
		std::cout << "trying to run." << '\n';
		app.run();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		//system("pause");	
		return EXIT_FAILURE;
	}

	// uncomment the following line to stop the console from closing immediately upon program crash
	//system("pause");
	return EXIT_SUCCESS;
}
