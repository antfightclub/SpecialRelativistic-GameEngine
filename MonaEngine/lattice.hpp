#include "mve_model.hpp"



namespace mve {
	class Lattice {
	public:

		
		
		Lattice(int range, int div, int innerDiv, int lineWidth, double scale) : L{ range }, N{ div }, c{ innerDiv }, lineWidth{ lineWidth } { makeLattice(div, range, scale); };

		~Lattice() {};

		void makeLattice(int N, int L, double scale);
		
		void add(double xx, double yy, double zz, double a);
		
		std::vector<glm::vec3> getVertices();
		//std::vector<uint32_t> getIndices();
	
	private:
		int L;	// range 
		int N;	// div
		int lineWidth = 1;
		int c = 5;	// innerDiv

		std::vector<glm::vec3> vertices{};
		//std::vector<uint32_t> indices{};
	};
}