#pragma once

#include "m4sta.h"
#include "../mve_game_object.hpp"
#include "mve_phasespace.hpp"

#include <vector>
#include <iostream>

using namespace m4sta;

namespace mve {
	struct LineContainer {
		double g0;
		double g1;
		double g2; 
		double g3;
	};
	
	class MveWorldLine {
	public:
		MveWorldLine(MveGameObject::id_t gameObjID, m4sta::mv firstEntry) : mveGameObjectID{ gameObjID } {
			Line.clear();
			init(firstEntry);
		}

		void init(m4sta::mv entry) {
			LineContainer firstEntry{
			entry.get_g0(),
			entry.get_g1(),
			entry.get_g2(),
			entry.get_g3()
			};
			Line.push_back(firstEntry);
			//this->n = 1;
			//this->last = -1;
		}

		void add(m4sta::mv lineEntry);

		void cut(int i);

		int searchPositionOnPLC(m4sta::mv Observer);

		MvePhaseSpace get_pos_vel_on_PLC(m4sta::mv Observer);
		
		size_t getEntryAmount() { return Line.size(); }

		

	private:
		//int n;
		//int last;
		std::vector<LineContainer> Line;
		MveGameObject::id_t mveGameObjectID;
	}; // end class MveWorldLine
} // end namespace mve