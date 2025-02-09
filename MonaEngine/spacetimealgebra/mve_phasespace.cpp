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
		position.set_g0(temp.get_g0() + velocity.get_g0() * ds);
		position.set_g1(temp.get_g1() + velocity.get_g1() * ds);
		position.set_g2(temp.get_g2() + velocity.get_g2() * ds);
		position.set_g3(temp.get_g3() + velocity.get_g3() * ds);

		double lorentzFactor = velocity.get_g0(); // Already done!

		mv tempvel = velocity;
		mv tempaccel = accel;

		double invLorentzFactor = 1.0 / lorentzFactor;

		tempaccel.set_g0(invLorentzFactor * (
			tempvel.get_g1() * tempaccel.get_g1()
			+ tempvel.get_g2() * tempaccel.get_g2()
			+ tempvel.get_g3() * tempaccel.get_g3()));

		std::cout << "acceleration = " << tempaccel.toString() << std::endl;

		
		//velocity.set_g1(velocity.get_g1() + finalvel.get_g1());
		//velocity.set_g2(velocity.get_g2() + finalvel.get_g2());
		//velocity.set_g3(velocity.get_g3() + finalvel.get_g3());
		
		// need a way to make relativistic velocity addition work!
		// it seems this doesn't work much - it allows to go faster
		// than light!
		velocity.set_g1(tempvel.get_g1() + (tempaccel.get_g1() * ds));
		velocity.set_g2(tempvel.get_g2() + (tempaccel.get_g2() * ds));
		velocity.set_g3(tempvel.get_g3() + (tempaccel.get_g3() * ds));
		
		velocity.set_g0(std::sqrt(1.0
			+ velocity.get_g1() * velocity.get_g1()
			+ velocity.get_g2() * velocity.get_g2()
			+ velocity.get_g3() * velocity.get_g3()));

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
		ret.set_g1(this->velocity.get_g1() * b);
		ret.set_g2(this->velocity.get_g2() * b);
		ret.set_g3(this->velocity.get_g3() * b);
		return ret;
	}

}//end namespace mve