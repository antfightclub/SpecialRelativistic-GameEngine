#include "mve_phasespace.hpp"

#include <cmath>

namespace mve {
	void MvePhaseSpace::transform(m4sta::vector accel, double ds) {
		m4sta::mv temp = position.get_g0() * g0 + position.get_g1() * g1 + position.get_g2() * g2 + position.get_g3() * g3;
		position.set_g0(temp.get_g0() + velocity.get_g0() * ds);
		position.set_g1(temp.get_g1() + velocity.get_g1() * ds);
		position.set_g2(temp.get_g2() + velocity.get_g2() * ds);
		position.set_g3(temp.get_g3() + velocity.get_g3() * ds);

		accel.set_g0(0.0);
		
		//mv finalvel = (v + u) * m4sta::versorInverse(1 + v * u);
		
		mv v = velocity * g0;
		mv u = accel * g0;

		mv newVel = (v + u) * m4sta::versorInverse(1 + v * u);
		velocity = newVel * ds;

		//velocity.set_g0(std::sqrt(1.0 ))
	}

}//end namespace mve