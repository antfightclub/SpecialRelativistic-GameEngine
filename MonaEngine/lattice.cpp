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
	std::vector<uint32_t> Lattice::getIndices() {
		if (this->indices.empty()) {
			throw std::runtime_error("Failed to get indices since index vector is empty!");
		}
		return this->indices;
	}

	void Lattice::makeLattice(int N, int L, int c, double scale) {
		if (!this->vertices.empty() && !this->indices.empty()) {
			throw std::runtime_error("MakeLattice: vertices or indices are not empty!");
		}
		//std::shared_ptr<MveModel> mveModel = MveModel::MveModel(mveDevice);
		std::cout << "Start of makeLattice!" << "\n";
		this->vertices.clear();
		this->indices.clear();
		//this->indices.push_back(static_cast<uint32_t>(0U));
		//int n = 2 * N + 1;

		double l = (double)L;
		double n = (double)N;

		double xx, yy, zz;
		for (int i = -N; i < N+1; i++) {
			xx = ((double)i + 0.5) * l / n;
			for (int j = -N; j < N+1; j++) {
				yy = ((double)j + 0.5) * l / n;
				for (int k = -N*c; k < N*c+1; k++) {
					zz = ((double)k + 0.5 * c) * l / (n * c);
					add(xx, yy, zz, k);
				}
			}
		}
		//std::cout << "first for loop complete!" << "\n";

		for (int i = -N; i < N + 1; i++) {
			xx = ((double)i + 0.5) * l / n;
			for (int j = -N; j < N + 1; j++) {
				zz = ((double)j + 0.5) * l / n;
				for (int k = -N * c; k < N * c + 1; k++) {
					yy = ((double)k + 0.5 * c) * l / (n * c);
					add(xx, yy, zz, k);
				}
			}
		}
		////std::cout << "second for loop complete!" << "\n";

		for (int i = -N; i < N + 1; i++) {
			zz = ((double)i + 0.5) * l / n;
			for (int j = -N; j < N + 1; j++) {
				yy = ((double)j + 0.5) * l / n;
				for (int k = -N * c; k < N * c + 1; k++) {
					xx = ((double)k + 0.5 * c) * l / (n * c);
					add(xx, yy, zz, k);
				}
			}
		}
		//std::cout << "third for loop complete!" << "\n";

		latticeUnit = L / N;
	}

	void Lattice::add(double xx, double yy, double zz, int a) {
		vertices.push_back(glm::vec3{ xx, yy, zz });
		if (a < N * c) {
			indices.push_back((uint32_t)std::floor(static_cast<uint32_t>(vertices.size())));
			indices.push_back((uint32_t)std::floor(static_cast<uint32_t>(vertices.size()-1U)));
		}
	}

	void Lattice::writeVerticesToFile() {
		std::ofstream outV{ "Vertices.txt" };
		if (!outV) {
			std::cerr << "Vertices.txt could not be opened for writing!\n";
			return;
		}
		for (glm::vec3& v : vertices) {
			outV << v.x << ", " << v.y << ", " << v.z << "\n";
		}
		return;
	}

	void Lattice::writeIndicesToFile() {
		std::ofstream outI{ "Indices.txt" };
		if (!outI) {
			std::cerr << "Indices.txt could not be opened for writing!\n";
			return;
		}
		for (uint32_t i : indices) {
			outI << i << "\n";
		}
		return;
	}


}
