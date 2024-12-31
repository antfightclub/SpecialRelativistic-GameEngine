#include "lattice.hpp"
#include "mve_device.hpp"

#include <vector>
#include <stdexcept>
#include <iostream>

namespace mve {

	std::vector<glm::vec3> Lattice::getVertices() {
		if (this->vertices.empty()) {
			throw std::runtime_error("Failed to get vertices since vertex vector is empty!");
		}
		return this->vertices;
	}
	/*std::vector<uint32_t> Lattice::getIndices() {
		if (this->indices.empty()) {
			throw std::runtime_error("Failed to get indices since index vector is empty!");
		}
		return this->indices;
	}*/

	void Lattice::makeLattice(int N, int L, int c, double scale) {
		//std::shared_ptr<MveModel> mveModel = MveModel::MveModel(mveDevice);
		std::cout << "Start of makeLattice!" << "\n";
		
		int n = 2 * N + 1;
		int xx, yy, zz;
		for (int i = -N; i < N + 1; i++) {
			xx = int((i + 0.5) * (L / N));
			for (int j = -N; j < N + 1; j++) {
				yy = int((j + 0.5) * (L / N));
				for (int k = -N*c; k < N*c + 1; k++) {
					zz = int((((k + 0.5) * c) * L) / (N * c));
					add(xx, yy, zz, k);
				}

			}
		}
		std::cout << "first for loop complete!" << "\n";

		for (int i = -N; i < N + 1; i++) {
			xx = int((i + 0.5) * (L / N));
			for (int j = -N; j < N + 1; j++) {
				zz = int((j + 0.5) * (L / N));
				for (int k = -N * c; k < N * c + 1; k++) {
					yy = int((((k + 0.5) * c) * L) / (N * c));
					add(xx, yy, zz, k);
				}

			}
		}
		std::cout << "second for loop complete!" << "\n";

		for (int i = -N; i < N + 1; i++) {
			zz = int((i + 0.5) * (L / N));
			for (int j = -N; j < N + 1; j++) {
				yy = int((j + 0.5) * (L / N));
				for (int k = -N * c; k < N * c + 1; k++) {
					xx = int((((k + 0.5) * c) * L) / (N * c));
					add(xx, yy, zz, k);
				}

			}
		}
		std::cout << "third for loop complete!" << "\n";

		latticeUnit = L / N;
	}

	void Lattice::add(double xx, double yy, double zz, double a) {
		vertices.push_back(glm::vec3{ xx, yy, zz });
		/*if (a < N * c) {
			indices.push_back(std::floor(static_cast<uint32_t>(vertices.size()) / 3 - 1));
			indices.push_back(std::floor(static_cast<uint32_t>(vertices.size()) / 3));
		}*/
	}



}
