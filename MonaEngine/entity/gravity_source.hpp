#pragma once

#include "../mve_game_object.hpp"
#include "../mve_model.hpp"
#include "../spacetimealgebra/m4sta.hpp"
#include "../spacetimealgebra/mve_worldline.hpp"

namespace mve {
	class GravitySource {
	public:
		GravitySource(MveWindow& mveWindow, MveGameObject& gameObject, double mass, m4sta::mv spacetimePosition, m4sta::mv rapidity);
		m4sta::mv position;
		m4sta::mv rapidity;
		double mass;

		void Action(GLFWwindow* window, double deltaTime);
		MvePhaseSpace getDrawData(m4sta::mv observerPosition);
		MveGameObject::id_t getGameObjectID() { return this->id; }

	private:
		MveWindow& mveWindow;
		MveGameObject::id_t id;

		MveWorldLine worldline;

		void init(mve::MveGameObject& gameObject) { this->id = gameObject.getId(); }
	};
}