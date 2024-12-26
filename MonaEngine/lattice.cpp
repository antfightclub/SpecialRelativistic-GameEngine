#include "lattice.hpp"
#include "mve_device.hpp"

#include <vector>
#include <stdexcept>

namespace mve {

	std::vector<glm::vec3> Lattice::getVertices() {
		if (this->vertices.empty()) {
			throw std::runtime_error("Failed to get vertices since vertex vector is empty!");
		}
		return this->vertices;
	}
	std::vector<uint32_t> Lattice::getIndices() {
		if (this->indices.empty()) {
			throw std::runtime_error("Failed to get indices since index vector is empty!");
		}
		return this->indices;
	}

	void Lattice::makeLattice(double N, double L, double scale) {
		//std::shared_ptr<MveModel> mveModel = MveModel::MveModel(mveDevice);
		int n = 2 * N + 1;
		int xx, yy, zz;
		for (int i = -N; i < N + 1; i++) {
			xx = (i + 0.5) * (L / N);
			for (int j = -N; j < N + 1; j++) {
				yy = (j + 0.5) * (L / N);
				for (int k = -N*c; k < N*c + 1; k++) {
					zz = (((k + 0.5) * c) * L) / (N * c);
					add(xx, yy, zz, k);
				}

			}
		}

		for (int i = -N; i < N + 1; i++) {
			xx = (i + 0.5) * (L / N);
			for (int j = -N; j < N + 1; j++) {
				zz = (j + 0.5) * (L / N);
				for (int k = -N * c; k < N * c + 1; k++) {
					yy = (((k + 0.5) * c) * L) / (N * c);
					add(xx, yy, zz, k);
				}

			}
		}

		for (int i = -N; i < N + 1; i++) {
			zz = (i + 0.5) * (L / N);
			for (int j = -N; j < N + 1; j++) {
				yy = (j + 0.5) * (L / N);
				for (int k = -N * c; k < N * c + 1; k++) {
					xx = (((k + 0.5) * c) * L) / (N * c);
					add(xx, yy, zz, k);
				}

			}
		}

	}

	void Lattice::add(double xx, double yy, double zz, double a) {
		vertices.push_back(glm::vec3{ xx, yy, zz });
		if (a < N * c) {
			indices.push_back(static_cast<uint32_t>(vertices.size()) / 3 - 1);
			indices.push_back(static_cast<uint32_t>(vertices.size()) / 3);
		}
	}



}
