#pragma once

#include "Vector4D.hpp"
#include "Quaternion.hpp"

#include <vector>
#include <iostream>

namespace Math {

	struct indexands {
		int index;
		double s;
	};



	// 
	struct EntityState {
		//Quaternion quaternion{ 0.0 };
		//???
	};

	struct StateOnPLC {
		EntityState state0{};
		EntityState state1{};
		double s;
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
			ix_s.index = 1;
			ix_s.s = 0.0;
		}

		void add(Vector4D line, EntityState state);
		
		void cut();

		int searchPositionOnPLC(Vector4D Xp);

		Vector4D getX_FP(Vector4D Xp_py, double w = 0.5);

		// Get X (spacetime position) and U (velocity)
		std::vector<Vector4D> getXU_OnPLC(Vector4D Xp_py);

		// Return StateOnPLC which contains two state objects as well as a double for time.
		// Get i by searchPositionOnPLC
		StateOnPLC getStateOnPLC(int i);

		// Python syntax would be to Line[-1] but not sure if std::vector allows that!
		Vector4D getLast();

		std::vector<Vector4D> getLastTwo();

		void printAllEntries();
		

	private:
		int n;
		int last;
		indexands ix_s;
		std::vector<Vector4D> Line;
		std::vector<EntityState> State;
		id_t mveGameObjectID;

	
		
	};
}