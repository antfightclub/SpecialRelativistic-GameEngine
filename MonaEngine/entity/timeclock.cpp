#include "timeclock.hpp"

namespace mve {
	TimeClock::TimeClock(MveWindow& mveWindow, MveGameObject& gameObject, float color[3], double blinkTime, m4sta::mv spacetimePosition)
		: mveWindow{ mveWindow }, 
		color{ color[0], color[1], color[2] }, 
		//blinktime(blinkTime), 
		spacetimePosition{spacetimePosition},
		worldline{gameObject.getId(), spacetimePosition} {
		this->init(gameObject);
	}

	void TimeClock::Action(GLFWwindow* window, double deltaTime) {
		//accumulator += deltaTime;
		//if (accumulator >= blinktime) {
		//	accumulator = 0.0;
		//	this->poweredState = !poweredState;
		//}
		spacetimePosition.set_g0(spacetimePosition.get_g0() + deltaTime);
		
		//std::cout << "spacetime position of timeclock = " << spacetimePosition.toString() << "\n";

		worldline.add(spacetimePosition);
	
	}

	TimeClockDrawData TimeClock::getDrawData(m4sta::mv observerPosition) {
		//std::cout << "getDrawData called on gameobject ID " << id << "\n";
		MvePhaseSpace P = this->worldline.get_pos_vel_on_PLC(observerPosition);
		return {
			P,
			{this->color[0], this->color[1], this->color[2]}
		};
	}

}