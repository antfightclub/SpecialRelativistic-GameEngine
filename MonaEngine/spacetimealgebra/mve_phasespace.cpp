#include "mve_phasespace.hpp"

#include <cmath>

namespace mve {
	void MvePhaseSpace::transform(m4sta::mv accel, double ds) {
		m4sta::mv temp = position;//position.get_g0() * g0 + position.get_g1() * g1 + position.get_g2() * g2 + position.get_g3() * g3;
		//position.set_scalar(temp.get_scalar() + velocity.get_scalar() * ds);
		//position.set_g0_g1(temp.get_g0_g1() + velocity.get_g0_g1() * ds);
		//position.set_g0_g2(temp.get_g0_g2() + velocity.get_g0_g2() * ds);
		//position.set_g0_g3(temp.get_g0_g3() + velocity.get_g0_g3() * ds);
		
		//double lorentz_factor = std::sqrt(1.0 + );

		double velx = velocity.get_g1();
		double vely = velocity.get_g2();
		double velz = velocity.get_g3();

		mv beta_hat = velocity * g0;
		double beta = norm(velocity); //?
		double lorentz_factor = std::sqrt(1.0 + velx * velx + vely * vely + velz * velz);
		mv L2 = lorentz_factor * (1 - beta * beta_hat);

		// This formula only works for spacetime split!...
		//mv newVel = (v + u) * m4sta::versorInverse(1 + v * u);
		mv acceleration =L2* accel;
		
		velocity +=  acceleration * ds;

		//velocity.set_g0(std::sqrt(1.0 ))
	}

	mv MvePhaseSpace::getResist(double b) {
		mv ret;
		ret.set_g0(0.0);
		ret.set_g1(this->velocity.get_g1() * b);
		ret.set_g2(this->velocity.get_g2() * b);
		ret.set_g3(this->velocity.get_g3() * b);
		return ret;
	}

}//end namespace mve