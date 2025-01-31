#include "mve_phasespace.hpp"

#include <cmath>

namespace mve {
	void MvePhaseSpace::transform(m4sta::mv accel, double ds) {
		m4sta::mv temp = position.get_g0() * g0 + position.get_g1() * g1 + position.get_g2() * g2 + position.get_g3() * g3;
		position.set_g0(temp.get_g0() + velocity.get_g0() * ds);
		position.set_g1(temp.get_g1() + velocity.get_g1() * ds);
		position.set_g2(temp.get_g2() + velocity.get_g2() * ds);
		position.set_g3(temp.get_g3() + velocity.get_g3() * ds);

		accel.set_g0(0.0);

		// v0 = initial velocity
		// v  = final velocity
		// w = (v + v0) / (|v + v0|)
		// or
		// w  = (v+v0) / (sqrt(2 * (1 + v inner v0)))
		// w is a unit vector
		// w from 3.37b (spacetime calculus, hestenes)
		m4sta::mv w = (temp + position) / std::sqrt(2 * (1 + sp(temp, position)));
		//m4sta::mv V = 

	}

}//end namespace mve