#pragma once

#include "entity.hpp"

#include "../mve_game_object.hpp"
#include "../mve_model.hpp"
#include "../spacetimealgebra/m4sta.h"

namespace mve {
	struct TimeClockDrawData {
		m4sta::mv split; // Importantly, this position should be the spacetime split!!
		bool poweredState;
		float color[3];
	};

	class TimeClock /* : public Entity*/ {
	public:
		TimeClock(MveWindow& mveWindow, MveGameObject& gameObject, float color[3], double blinkTime, m4sta::mv spacetimePosition);
		m4sta::mv spacetimePosition;
		float color[3] = { 0.5f, 0.5f, 0.5f };

		void Action(GLFWwindow* window, double deltaTime);
		TimeClockDrawData getDrawData(m4sta::mv observerPosition);

	private:
		MveWindow& mveWindow;
		MveGameObject::id_t id;
		double blinktime = 1.0;
		double accumulator = 0.0;
		bool poweredState = true;

		void init(mve::MveGameObject& gameObject) { this->id = gameObject.getId(); }

	};
}