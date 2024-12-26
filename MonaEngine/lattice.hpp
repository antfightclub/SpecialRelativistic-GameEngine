#include "mve_model.hpp"



namespace mve {
	class Lattice {
	public:
		
		//Lattice();

		//~Lattice();

		void makeLattice(double N, double L, double scale);
	
	private:
		double range = 100.0;
		double div = 30;
		int lineWidth = 1;
		int innerDiv = 5;
	};
}