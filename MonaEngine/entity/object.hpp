#pragma once

#include "../mve_game_object.hpp"
#include "../mve_model.hpp"
#include "../spacetimealgebra/m4sta.hpp"
#include "../spacetimealgebra/mve_worldline.hpp"

namespace mve {
	struct ObjectDrawData {
		MvePhaseSpace phaseSpace;
	};

	class TestObject {
	public:
		TestObject(MveWindow& mveWindow, MveGameObject& gameObject, m4sta::mv spacetimePosition);
		m4sta::mv spacetimePosition;
		m4sta::mv accelDirection{};

		void Action(GLFWwindow* window, double deltaTime);

		ObjectDrawData getDrawData(m4sta::mv observerPosition);
		MveGameObject::id_t getGameObjectId() { return this->id; }
		size_t getWorldlineEntryAmount() { return worldline.getEntryAmount(); }

	private:
		MveWindow& mveWindow;
		MveGameObject::id_t id;
		MveWorldLine worldline;
		MvePhaseSpace P;

		void init(mve::MveGameObject& gameObject) { this->id = gameObject.getId(); }

		m4sta::mv getAcceleration(double deltaTime);
		void changeDirection(double deltaTime);

	};

}