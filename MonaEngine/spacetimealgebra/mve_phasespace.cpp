#include "mve_phasespace.hpp"

#include <cmath>
#include <iostream>

namespace mve {
	void MvePhaseSpace::transform(m4sta::mv accel, double ds) {
		m4sta::mv temp = position;//position.get_g0() * g0 + position.get_g1() * g1 + position.get_g2() * g2 + position.get_g3() * g3;
		position.set_g0(temp.get_g0() + velocity.get_g0() * ds);
		position.set_g1(temp.get_g1() + velocity.get_g1() * ds);
		position.set_g2(temp.get_g2() + velocity.get_g2() * ds);
		position.set_g3(temp.get_g3() + velocity.get_g3() * ds);
		
		//std::cout << "accel   : " << accel.toString() << std::endl << std::endl;
		//accel.set_g0(0.0);

		// Constructing the inverse lorentz transformation to get back to background frame
		double betax = -velocity.get_g1();
		double betaz = -velocity.get_g2();
		double betay = -velocity.get_g3(); 

		mv Bhat10 = g1 * g0;
		mv Bhat20 = g2 * g0;
		mv Bhat30 = g3 * g0;

		double rapidityx = 0.5 * (log((1.0 + betax) / (1.0 - betax)));
		double rapidityy = 0.5 * (log((1.0 + betay) / (1.0 - betay)));
		double rapidityz = 0.5 * (log((1.0 + betaz) / (1.0 - betaz)));

		mv Lx = exp(0.5 * rapidityx * Bhat10);
		mv Ly = exp(0.5 * rapidityy * Bhat20);
		mv Lz = exp(0.5 * rapidityz * Bhat30);

		mv accelx = accel.get_g1() * g1;
		mv accely = accel.get_g2() * g2;
		mv accelz = accel.get_g3() * g3;

		accelx *= ds;
		accely *= ds;
		accelz *= ds;

		std::cout << "betax             : " << betax << std::endl;
		std::cout << "betay             : " << betay << std::endl;
		std::cout << "betaz             : " << betaz << std::endl;

		std::cout << "rapidityx         : " << rapidityx << std::endl;
		std::cout << "rapidityy         : " << rapidityy << std::endl;
		std::cout << "rapidityz         : " << rapidityz << std::endl;

		std::cout << "Lx                : " << Lx.toString() << std::endl;
		std::cout << "Ly                : " << Ly.toString() << std::endl;
		std::cout << "Lz                : " << Lz.toString() << std::endl;

		accelx = (~Lx) * accelx * Lx;
		accely = (~Ly) * accely * Ly;
		accelz = (~Lz) * accelz * Lz;

		std::cout << "~Lx * accelx * Lx : " << accelx.toString() << std::endl;
		std::cout << "~Ly * accely * Ly : " << accely.toString() << std::endl;
		std::cout << "~Lz * accelz * Lz : " << accelz.toString() << std::endl;
	

		mv tempvel = velocity; //velocity.get_g1() * g1 + velocity.get_g2() * g2 + velocity.get_g3() * g3;
		mv tempaccel = accelx + accely + accelz; //accelx.get_g1() * g1 + accely.get_g2() * g2 + accelz.get_g3() * g3;
		//tempaccel *= ds;

		//tempvel = tempvel * g0;
		tempaccel = tempaccel * g0;
		std::cout << "tempvel           : " << tempvel.toString() << std::endl;
		std::cout << "tempaccel         : " << tempaccel.toString() << std::endl;

		//mv finalvel = div(tempvel + tempaccel, 1 + (m4sta::sp(tempvel, tempaccel)));
		mv finalvel = (tempvel + tempaccel) * versorInverse(1 + tempvel * tempaccel);
		//finalvel = finalvel;
		finalvel = g0 * finalvel;

		std::cout << "finalvel          : " << finalvel.toString() << std::endl;
		std::cout << std::endl;

		
		//velocity.set_g1(velocity.get_g1() + finalvel.get_g1());
		//velocity.set_g2(velocity.get_g2() + finalvel.get_g2());
		//velocity.set_g3(velocity.get_g3() + finalvel.get_g3());
		
		// need a way to make relativistic velocity addition work!
		// it seems this doesn't work much - it allows to go faster
		// than light!
		velocity.set_g1(tempvel.get_g1() + (accelx.get_g1()));
		velocity.set_g2(tempvel.get_g2() + (accely.get_g2()));
		velocity.set_g3(tempvel.get_g3() + (accelz.get_g3()));
		
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