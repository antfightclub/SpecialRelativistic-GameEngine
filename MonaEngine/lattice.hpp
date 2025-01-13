#pragma once
#include "mve_model.hpp"

#include <iostream>
#include <fstream>


namespace mve {
	class Lattice {
	public:

		
		
		Lattice(int range, int div, int innerDiv, int lineWidth, double scale) : L{ range }, N{ div }, c{ innerDiv }, lineWidth{ lineWidth } {
			this->L = int((double)range * scale);
			makeLattice(this->N, this->L);
		
		};

		~Lattice() {};

		void makeLattice(int N, int L);
		
		void add(double xx, double yy, double zz, int a);
		
		std::vector<glm::vec3> getVertices();
		std::vector<uint32_t> getIndices();
		
		void writeVerticesToFile();
		void writeIndicesToFile();
	
	private:
		int L;	// range 
		int N;	// div
		int lineWidth = 1;
		int c = 5;	// innerDiv
		double latticeUnit;

		std::vector<glm::vec3> vertices{};
		std::vector<uint32_t> indices{};
	};
}