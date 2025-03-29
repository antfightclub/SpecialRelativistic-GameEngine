#pragma once

#include "m4sta.hpp"

using namespace m4sta;

namespace mve {

	class MvePhaseSpace {
	public:
		m4sta::mv position;
		m4sta::mv rapidity;

		MvePhaseSpace() : position{}, rapidity{} {}
		MvePhaseSpace(m4sta::mv pos, m4sta::mv vel) : position{pos}, rapidity{vel} {}

		void transform(m4sta::mv accel, double deltaSeconds);

		mv getResist(double b);
	};

}//end namespace mve