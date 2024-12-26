#include "mve_model.hpp"



namespace mve {
	class Lattice {
	public:

		
		
		//Lattice();

		//~Lattice();
		
		void makeLattice(double N, double L, double scale);
		
		void add(double xx, double yy, double zz, double a);
		
		std::vector<glm::vec3> getVertices();
		std::vector<uint32_t> getIndices();
	
	private:
		double L = 100.0;	// range 
		double N = 30.0;	// div
		//int lineWidth = 1;
		int c = 5;	// innerDiv

		std::vector<glm::vec3> vertices{};
		std::vector<uint32_t> indices{};
	};
}