#pragma once

#include "m4sta.h"
#include "../mve_game_object.hpp"
#include "mve_phasespace.hpp"

#include <vector>
#include <iostream>

using namespace m4sta;

namespace mve {
	
	class MveWorldLine {
	public:
		MveWorldLine(MveGameObject::id_t gameObjID, m4sta::mv firstEntry) : mveGameObjectID{ gameObjID } {
			Line.clear();
			init(firstEntry);
		}

		void init(m4sta::mv firstEntry) {
			Line.push_back(firstEntry);
			this->n = 1;
			this->last = -1;
		}

		void add(m4sta::mv lineEntry);

		void cut();

		int searchPositionOnPLC(m4sta::mv Observer);

		MvePhaseSpace get_pos_vel_on_PLC(m4sta::mv Observer);

		

	private:
		int n;
		int last;
		std::vector<m4sta::mv> Line;
		MveGameObject::id_t mveGameObjectID;
	}; // end class MveWorldLine
} // end namespace mve