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
		int start = 1;
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

	std::vector<Vector4D> WorldLine::getXU_OnPLC(Vector4D Xp_py) {
		Vector4D Xp = Xp_py;
		int i = searchPositionOnPLC(Xp);
		if (i == -1) {
			return std::vector<Vector4D> {Vector4D{ 0.0 }, Vector4D{ 0.0 }}; // In place of None, return vector of two 0.0 vectors
		}
		Vector4D X0 = this->Line[i - 1];
		Vector4D X1 = this->Line[i];
		Vector4D dX = X1 - X0;
		Vector4D dY = Xp - X0;
		double a = dX.lorentzianSquaredNorm();
		double b = dX.lorentzianInnerProduct(dY);
		double c = dY.lorentzianSquaredNorm();
		double s = (b + std::sqrt(b * b - a * c)) / a;

		this->ix_s.s = s;
		dX /= std::sqrt(-a);

		std::vector<Vector4D> ret;
		ret.push_back(X0.getDivPoint(X1, s));
		ret.push_back(dX);
		return ret;
	}

	StateOnPLC WorldLine::getStateOnPLC(int i) {
		//throw std::runtime_error("WorldLine::GetStateOnPLC() not yet implemented!");
		
		return StateOnPLC{
			this->State[i],
			this->State[i - 1],
			this->ix_s.s
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