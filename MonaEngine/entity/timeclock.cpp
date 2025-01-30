#include "timeclock.hpp"

namespace mve {
	TimeClock::TimeClock(MveWindow& mveWindow, MveGameObject& gameObject, float color[3], double blinkTime, m4sta::mv spacetimePosition) : mveWindow{ mveWindow }, color{ color[0], color[1], color[2] }, blinktime(blinkTime), spacetimePosition{spacetimePosition} {
		this->init(gameObject);
	}

	void TimeClock::Action(GLFWwindow* window, double deltaTime) {
		accumulator += deltaTime;
		if (accumulator >= blinktime) {
			accumulator = 0.0;
			this->poweredState = !poweredState;
		}
		spacetimePosition.set_g0(spacetimePosition.get_g0() + deltaTime);
	}

	TimeClockDrawData TimeClock::getDrawData(m4sta::mv observerPosition) {
		// Spacetime split w.r.t. the player's g0!
		m4sta::mv ret = this->spacetimePosition * m4sta::g0;// observerPosition.get_g0();

		return {
			ret,
			this->poweredState,
			{this->color[0], this->color[1], this->color[2]}
		};
	}

}