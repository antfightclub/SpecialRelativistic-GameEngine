#include "PhaseSpace.hpp"

namespace Math {

	Vector4D PhaseSpace::getResist(double b) {
		return Vector4D{
			0.0f,
			this->U.getX() * b,
			this->U.getY() * b,
			this->U.getZ() * b
		};
	}

	void PhaseSpace::transform(Vector4D acceleration, double ds) {
		Vector4D temp = Vector4D{ acceleration.getT(), acceleration.getX(), acceleration.getY(), acceleration.getZ() };
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
	}

}