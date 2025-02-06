#include "mve_worldline.hpp"


namespace mve {

	void MveWorldLine::add(m4sta::mv lineEntry) {
		LineContainer entry{
			lineEntry.get_g0(),
			lineEntry.get_g1(),
			lineEntry.get_g2(),
			lineEntry.get_g3()
		};
		this->Line.push_back(entry);
		//std::cout << "adding new line entry   = " << lineEntry.toString() << "\n";
		//this->n = this->Line.size();
	}

	void MveWorldLine::cut(int i) {
		if (this->Line.size() >= 4000) { 
			this->Line.erase(Line.begin(), Line.begin());
		}
	}

	int MveWorldLine::searchPositionOnPLC(m4sta::mv Observer) {
		//std::cout << "line.size() = " << Line.size() << "\n";
		for (int i = 1; i < Line.size(); i++) {
			LineContainer temp = this->Line[i];
			//m4sta::mv difference = Observer - temp;
			//std::cout << "value of temp  = " << temp.toString() << "\n";
			//std::cout << "value of diff  = " << difference.toString() << "\n";

			double g0 = Observer.get_g0() - temp.g0;
			double g1 = Observer.get_g1() - temp.g1;
			double g2 = Observer.get_g2() - temp.g2;
			double g3 = Observer.get_g3() - temp.g3;
			

			//double normTo = m4sta::norm2(Observer - temp).get_scalar();
			double normTo = g0 * g0 - g1 * g1 - g2 * g2 - g3 * g3;
			//std::cout << "normTo   = " << normTo << "\n";
			//std::cout << "temp time = " << temp.get_g0() << " and observer time = " << observerTime << "\n";
			bool condition1 = Observer.get_g0() < temp.g0;
			bool condition2 = normTo > 0.0;
			//std::cout << "i = "  << i <<  ", condition 1 = " << condition1 << " and condition 2 = " << condition2 << "normto = " << normTo << "\n";

			if (!(condition1) && !(condition2)) {
				//std::cout << "i = " << i << "\n";
				return i;
			}
			else {
				return Line.size()-1; // ... if you go too fast (I think somewhere like 0.9c?) the above condition will fail... Can just reply with the newest instead.
			}
		}
		
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

		LineContainer zero = this->Line[i - 1];
		LineContainer one  = this->Line[i];

		m4sta::mv X0 = m4sta::g0 * zero.g0 + m4sta::g1 * zero.g1 + m4sta::g2 * zero.g2 + m4sta::g3 * zero.g3;
		m4sta::mv X1 = m4sta::g0 *  one.g0 + m4sta::g1 *  one.g1 + m4sta::g2 *  one.g2 + m4sta::g3 *  one.g3;
		m4sta::mv dX = X1 - X0;
		m4sta::mv dY = O  - X0;

		double alpha = m4sta::norm2(dX);//.get_scalar();
		double beta = m4sta::sp(dX, dY);
		double gamma = m4sta::norm2(dY);//.get_scalar();
		double sigma = (beta - std::sqrt(beta * beta - alpha * gamma)) / alpha; // [0, 1)
		//dX /= std::sqrt(-alpha);
		dX = m4sta::div(dX, std::sqrt(-alpha));

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
		//cut(i);
		return ret;
	}

}