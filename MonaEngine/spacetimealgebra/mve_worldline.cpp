#include "mve_worldline.hpp"


namespace mve {

	void MveWorldLine::add(m4sta::mv lineEntry) {
		this->Line.push_back(lineEntry);
		//std::cout << "adding new line entry   = " << lineEntry.toString() << "\n";
		this->n += 1;
	}

	void MveWorldLine::cut() {
		throw std::runtime_error("MveWorldline::Cut() not yet implemented!");
	}

	int MveWorldLine::searchPositionOnPLC(m4sta::mv Observer) {
		//double observerTime = Observer.get_g0();
		//std::cout << "observer time =  " << observerTime << "\n";
		//m4sta::mv O = Observer;
		//m4sta::mv temp = m4sta::mv{};
		//std::cout << " ******  \n";
		for (int i = 1; i < this->n; i++) {
			m4sta::mv temp = this->Line[i];
			m4sta::mv difference = Observer - temp;
			//std::cout << "value of temp  = " << temp.toString() << "\n";
			//std::cout << "value of diff  = " << difference.toString() << "\n";

			double g0 = Observer.get_g0() - temp.get_g0();
			double g1 = Observer.get_g1() - temp.get_g1();
			double g2 = Observer.get_g2() - temp.get_g2();
			double g3 = Observer.get_g3() - temp.get_g3();
			

			//double normTo = m4sta::norm2(Observer - temp).get_scalar();
			double normTo = g0 * g0 - g1 * g1 - g2 * g2 - g3 * g3;
			//std::cout << "normTo   = " << normTo << "\n";
			//std::cout << "temp time = " << temp.get_g0() << " and observer time = " << observerTime << "\n";
			if (temp.get_g0() > Observer.get_g0() || normTo < 0.0) {
				//std::cout << "returning i = " << i << "\n\n";
				return i;
			}
		}
		//std::cout << "returning -1!\n\n";
		return -1;
	}

	MvePhaseSpace MveWorldLine::get_pos_vel_on_PLC(m4sta::mv Observer) {
		m4sta::mv O = Observer;
		int i = searchPositionOnPLC(O);
		//std::cout << "searchPositionOnPLC returned int = " << i << "\n";
		if (i == -1) {
			return MvePhaseSpace{ m4sta::mv{}, m4sta::mv{ } };
		}
		//std::cout << "position on PLC   = " << i << "\n";

		m4sta::mv X0 = this->Line[i - 1];
		m4sta::mv X1 = this->Line[i];
		m4sta::mv dX = X1 - X0;
		m4sta::mv dY = O  - X0;

		double alpha = m4sta::norm2(dX).get_scalar();
		double beta = m4sta::sp(dX, dY);
		double gamma = m4sta::norm2(dY).get_scalar();
		double sigma = (beta - std::sqrt(beta * beta - alpha * gamma)) / alpha; // [0, 1)
		dX /= std::sqrt(-alpha);

		double tt = X0.get_g0() * (1 - sigma) + X1.get_g0() * (sigma);
		double xx = X0.get_g1() * (1 - sigma) + X1.get_g1() * (sigma);
		double yy = X0.get_g2() * (1 - sigma) + X1.get_g2() * (sigma);
		double zz = X0.get_g3() * (1 - sigma) + X1.get_g3() * (sigma);

		m4sta::mv retur = tt * m4sta::g0 - xx * m4sta::g1 - yy * m4sta::g2 - zz * m4sta::g3;
		//std::cout << "ret                     = " << retur.toString() << "\n";
		//std::cout << "(X0 * (1 - sigma) + X1) = " << (X0 * (1 - sigma) + X1).toString() << "\n";
		
		//std::cout << "***** \n\n";

		MvePhaseSpace ret{
			retur, //X0 * (1 - sigma) + X1,
			dX
		};
		return ret;
	}

}