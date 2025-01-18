#pragma once

#include "Vector4D.hpp"
#include "Quaternion.hpp"
#include "PhaseSpace.hpp"

#include <vector>
#include <iostream>

namespace Math {

	struct PLCInterpolateInfo {
		int index;		// index of worldline
		double sigma;	// between 0 and 1
	};

	// Represents a state of an entity, usually after interpolation between worldline entries.
	struct EntityState {
		Quaternion quaternion{ 1.0, 0.0, 0.0, 0.0 };
	};

	struct StateOnPLC {
		EntityState state0{};
		EntityState state1{};
		double sigma;
	};

	class WorldLine {
	public:
		using id_t = unsigned int;
		
		WorldLine(id_t gameObjID, Vector4D firstX, EntityState firstState) : mveGameObjectID{gameObjID} {
			Line.clear();
			State.clear();
			init(firstX, firstState);
		}

		void init(Vector4D line, EntityState state) {
			Line.push_back(line);
			State.push_back(state);
			this->n = 1;
			this->last = -1;
			plcInterpolateInfo.index = 1;
			plcInterpolateInfo.sigma = 0.0;
		}

		void add(Vector4D lineEntry, EntityState stateEntry);
		
		void cut();

		int searchPositionOnPLC(Vector4D Xp);

		Vector4D getX_FP(Vector4D Xp_py, double w = 0.5);

		// Get X (spacetime position) and U (velocity)
		PhaseSpace getXU_OnPLC(Vector4D Xp_py);

		// Only call this after getXU_OnPLC!
		StateOnPLC getStateOnPLC();

		// Python syntax would be to Line[-1] but not sure if std::vector allows that!
		Vector4D getLast();

		std::vector<Vector4D> getLastTwo();

		void printAllEntries();
		

	private:
		int n;
		int last;
		PLCInterpolateInfo plcInterpolateInfo;
		std::vector<Vector4D> Line;
		std::vector<EntityState> State;
		id_t mveGameObjectID;		
	};
}