#pragma once

#include "m4sta.h"

using namespace m4sta;

namespace mve {

	class MvePhaseSpace {
	public:
		m4sta::mv position;
		m4sta::mv velocity;

		MvePhaseSpace(m4sta::mv pos, m4sta::mv vel) : position{pos}, velocity{vel} {}

		void transform(m4sta::mv accel, double deltaSeconds);
	};

}//end namespace mve