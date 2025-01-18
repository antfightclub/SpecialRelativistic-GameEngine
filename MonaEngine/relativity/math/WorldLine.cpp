#include "WorldLine.hpp"

namespace Math {
	
	void WorldLine::add(Vector4D line, Math::EntityState state) {
		this->Line.push_back(line);
		this->State.push_back(state);
		this->n += 1;
	}

	void WorldLine::cut() {
		throw std::runtime_error("Worldline::Cut() not yet implemented!");
	}

	int WorldLine::searchPositionOnPLC(Vector4D Xp) {
		//throw std::runtime_error("WorldLine Search Position on PLC not yet implemented!");
		double Xpt = Xp.getT();
		int start = 1;		// This starts from the first index... it could get slow real quick! Need a way of specifying the "worst case".
		int i;
		Vector4D X = Vector4D{};
		for (i = start; i < this->n; i++) {
			X = this->Line[i];
			if (X.getT() > Xpt || Xp.lorentzianSquaredNormTo(X) > 0.0) {
				return i;
			}
		}
		return -1;
	}

	Vector4D WorldLine::getX_FP(Vector4D Xp_py, double w) {
		Vector4D Xp = Xp_py;
		int i = this->searchPositionOnPLC(Xp);
		if (i == -1) {
			return Vector4D{ 0.0, 0.0, 0.0, 0.0 }; // In place of None, return a 0.0 vector. 
		}
		Vector4D X0 = this->Line[i - 1];
		Vector4D X1 = this->Line[i];
		Vector4D dX = X0 - X1;
		Vector4D dY = X0 - Xp;
		double a = dX.lorentzianSquaredNorm();
		double b = dX.lorentzianInnerProduct(dY);
		double s, c;

		if (w == 0.5) {
			s = b / a;
		}
		else {
			c = dY.lorentzianSquaredNorm();
			s = (b + (1.0 - 2.0 * w) * std::sqrt(b * b - a * c)) / a;
		}
		return X0.getDivPoint(X1, s);
	}

	PhaseSpace WorldLine::getXU_OnPLC(Vector4D Xp_py) {
		Vector4D Xp = Xp_py;
		// Iteratively check if points are on the past side of Xp's PLC
		// Return the first index of this worldline that is on the future side
		// of the PLC. Then linearly interpolate between the points on either side of PLC.
		int i = searchPositionOnPLC(Xp);
		if (i == -1) {
			return PhaseSpace{ Vector4D{0.0, 0.0, 0.0, 0.0}, Vector4D{0.0, 0.0, 0.0, 0.0} }; // if no position is found, return a zero-initialized PhaseSpace.
		}
		// See https://arxiv.org/abs/1703.07063 page 19 and 20, section 3.3. for a description of this
		// Linearly interpolate between the two points 
		Vector4D X0 = this->Line[i - 1];		// This point sits *just* on the past side of the PLC of Xp
		Vector4D X1 = this->Line[i];			// This point sits *just* on the future side of the PLC of Xp
		Vector4D dX = X1 - X0;					// Difference between the two worldline points on each side of the PLC.
		Vector4D dY = Xp - X0;					// Difference between the observer Xp and the past-side point of X0.
		double alpha = dX.lorentzianSquaredNorm();
		double beta = dX.lorentzianInnerProduct(dY);
		double gamma = dY.lorentzianSquaredNorm();
		double sigma = (beta + std::sqrt(beta * beta - alpha * gamma)) / alpha; // Should be a value between 0 and 1
		this->plcInterpolateInfo.index = i;
		this->plcInterpolateInfo.sigma = sigma;
		dX /= std::sqrt(-alpha);

		PhaseSpace ret{
			X0.getDivPoint(X1, sigma),			// this finds the "middle" point between X0(past side) and X1(future side) using the sigma value between 0 and 1. 
			dX									// dX as above is the velocity between the two points on the worldline (calculated by the difference between the two points X0 and X1
		};
		return ret;
	}
	
	// Only call this after getXU_OnPLC - it updates plcInterpolateInfo.
	StateOnPLC WorldLine::getStateOnPLC() {
		//throw std::runtime_error("WorldLine::GetStateOnPLC() not yet implemented!");
		
		return StateOnPLC{
			this->State[plcInterpolateInfo.index],
			this->State[plcInterpolateInfo.index - 1],
			this->plcInterpolateInfo.sigma
		};

	}

	std::vector<Vector4D> WorldLine::getLastTwo() {
		return std::vector<Vector4D> {this->Line[this->n-1], this->Line[this->n - 2]};
	}


	void WorldLine::printAllEntries() {
		for (int i = 0; i < Line.size(); i++) {
			std::cout << "Worldline[" << i << "] = {" <<
				Line[i].getT() << ", " << Line[i].getX() << ", " << Line[i].getY() << ", " << Line[i].getZ() << "} ^\n";
		}
	}

}