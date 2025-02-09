#include "mve_phasespace.hpp"

#include <cmath>
#include <iostream>

namespace mve {
	void MvePhaseSpace::transform(m4sta::mv accel, double ds) {
		// The transform method assumes delta time is given as proper time 
		// meaning the time that is passing for the observer
		// The acceleration is given as a direction of a magnitude specified by the entity
		// for the player, it is "0.2", and this is additionally multiplied by deltatime


		m4sta::mv temp = position;//position.get_g0() * g0 + position.get_g1() * g1 + position.get_g2() * g2 + position.get_g3() * g3;
		position.set_g0(temp.get_g0() + rapidity.get_g0() * ds);
		position.set_g1(temp.get_g1() + rapidity.get_g1() * ds);
		position.set_g2(temp.get_g2() + rapidity.get_g2() * ds);
		position.set_g3(temp.get_g3() + rapidity.get_g3() * ds);

		double lorentzFactor = rapidity.get_g0(); // Already done!

		//double x = rapidity.get_g1();
		//double y = rapidity.get_g2();
		//double z = rapidity.get_g3();
		//double xx = x * x;
		//double yy = y * y;
		//double zz = z * z;

		//double invLorentzFactor = std::sqrt(1 - (xx + yy + zz));

		mv temprapidity = rapidity;
		mv tempaccel = accel;

		temprapidity.set_g0(0.0);
		tempaccel.set_g0(0.0);
		//mv newvel = velocity + (tempaccel);
		
		double magRapidity = norm(temprapidity);
		std::cout << "magnitude of rapidity = " << magRapidity << std::endl;
		double beta = tanh(magRapidity);
		std::cout << "beta                  = " << beta << std::endl;
		
		
		// need a way to make relativistic velocity addition work!
		// it seems this doesn't work much - it allows to go faster
		// than light!

		// Addendum to above note: After a few days of wailing around,
		// it seems that the "velocity" here can be instead interpreted
		// as a "rapidity" that can be added to as normal. Then the actual
		// velocity can be found by beta = v / C = tanh(rapidity)
		// and the lorentz factor can also easily be found by cosh(rapidity)

		rapidity.set_g1(temprapidity.get_g1() + (tempaccel.get_g1() * ds));
		rapidity.set_g2(temprapidity.get_g2() + (tempaccel.get_g2() * ds));
		rapidity.set_g3(temprapidity.get_g3() + (tempaccel.get_g3() * ds));
		//
		rapidity.set_g0(std::sqrt(1.0
			+ rapidity.get_g1() * rapidity.get_g1()
			+ rapidity.get_g2() * rapidity.get_g2()
			+ rapidity.get_g3() * rapidity.get_g3()));

		//double lorentz_factor = std::sqrt(1.0 + );

		//double velx = velocity.get_g1();
		//double vely = velocity.get_g2();
		//double velz = velocity.get_g3();
		//
		//mv beta_hat = velocity * g0;
		//double beta = norm(velocity); //?
		//double lorentz_factor = std::sqrt(1.0 + velx * velx + vely * vely + velz * velz);
		//mv L2 = lorentz_factor * (1 - beta * beta_hat);
		//
		//// This formula only works for spacetime split!...
		////mv newVel = (v + u) * m4sta::versorInverse(1 + v * u);
		//mv acceleration =L2* accel;
		//
		//velocity +=  acceleration * ds;

		//velocity.set_g0(std::sqrt(1.0 ))
	}

	mv MvePhaseSpace::getResist(double b) {
		mv ret;
		ret.set_g0(0.0);
		ret.set_g1(this->rapidity.get_g1() * b);
		ret.set_g2(this->rapidity.get_g2() * b);
		ret.set_g3(this->rapidity.get_g3() * b);
		return ret;
	}

}//end namespace mve