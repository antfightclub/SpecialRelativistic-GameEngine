#include "mve_phasespace.hpp"

#include <glm.hpp>

#include <cmath>
#include <iostream>

namespace mve {
	void MvePhaseSpace::transform(m4sta::mv accel, double ds) {
		// The transform method assumes delta time is given as proper time 
		// meaning the time that is passing for the observer
		// The acceleration is given as a direction of a magnitude specified by the entity
		// for the player, it is "0.2", and this is additionally multiplied by deltatime

		/*void PhaseSpace::transform(Vector4D acceleration, double ds) {
			Vector4D temp = Vector4D{ this->X.getT(), this->X.getX(), this->X.getY(), this->X.getZ() };
			this->X.setT(temp.getT() + this->U.getT() * ds);
			this->X.setX(temp.getX() + this->U.getX() * ds);
			this->X.setY(temp.getY() + this->U.getY() * ds);
			this->X.setZ(temp.getZ() + this->U.getZ() * ds);
			acceleration.setT(0.0f);
			Matrix44 L = Matrix44::Lorentz(-this->U);
			Vector4D accel = L.getTransform(acceleration);
			double r = accel.length();
			if (r > 10.0) {
				this->U += accel * (ds * (10.0 / r));
			}
			else {
				this->U += accel * ds;
			}
			this->U.setT(std::sqrt(
				1.0
				+ this->U.getX() * this->U.getX()
				+ this->U.getY() * this->U.getY()
				+ this->U.getZ() * this->U.getZ()
			));
		}*/

		mv temp = this->position;
		this->position.set_g0(temp.get_g0() + this->rapidity.get_g0() * ds);
		this->position.set_g1(temp.get_g1() + this->rapidity.get_g1() * ds);
		this->position.set_g2(temp.get_g2() + this->rapidity.get_g2() * ds);
		this->position.set_g3(temp.get_g3() + this->rapidity.get_g3() * ds);

		accel.set_g0(0.0);


		// 
		double rapX = -this->rapidity.get_g1();
		double rapY = -this->rapidity.get_g2();
		double rapZ = -this->rapidity.get_g3();

		double rap = std::sqrt(rapX * rapX + rapY * rapY + rapZ * rapZ); // Magnitude of rapidity
		m4sta::mv unitDir = m4sta::unit(rapidity);

		double n_x = unitDir.get_g1();
		double n_y = unitDir.get_g2();
		double n_z = unitDir.get_g3();

		double cosh = std::cosh(rap);
		double sinh = std::sinh(rap);

		std::cout << "cosh: " << cosh << std::endl;
		std::cout << "sinh: " << sinh << std::endl;

		glm::mat4 L{ 1.f };

		if (std::tanh(rap) > 0.00001) {
			L = glm::mat4{
				1 + (cosh - 1) * n_x * n_x,		(cosh - 1) * n_x * n_y,		(cosh - 1) * n_x * n_z, -n_x * sinh,
					(cosh - 1) * n_y * n_x, 1 + (cosh - 1) * n_y * n_y,		(cosh - 1) * n_y * n_z, -n_y * sinh,
					(cosh - 1) * n_z * n_x,		(cosh - 1) * n_z * n_y, 1 + (cosh - 1) * n_z * n_z, -n_z * sinh,
							   -n_x * sinh,				   -n_y * sinh,				   -n_z * sinh,			cosh
			};
		}
		
		double t, x, y, z, tt, xx, yy, zz;

		t = accel.get_g0();
		x = accel.get_g1();
		y = accel.get_g2();
		z = accel.get_g3();

		tt = L[3][3] * t + L[0][3] * x + L[1][3] * y + L[2][3] * z;
		xx = L[3][0] * t + L[0][0] * x + L[1][0] * y + L[2][0] * z;
		yy = L[3][1] * t + L[0][1] * x + L[1][1] * y + L[2][1] * z;
		zz = L[3][2] * t + L[0][2] * x + L[1][2] * y + L[2][2] * z;

		mv acceleration = g0 * tt + g1 * xx + g2 * yy + g3 * zz;

		this->rapidity += acceleration * ds;
		
		this->rapidity.set_g0(
			std::sqrt(
				1.0
				+ this->rapidity.get_g1() * this->rapidity.get_g1()
				+ this->rapidity.get_g2() * this->rapidity.get_g2()
				+ this->rapidity.get_g3() * this->rapidity.get_g3()));




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