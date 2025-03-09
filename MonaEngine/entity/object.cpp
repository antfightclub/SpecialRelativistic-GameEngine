#include "object.hpp"

namespace mve {
	TestObject::TestObject(MveWindow& mveWindow, MveGameObject& gameObject, m4sta::mv spacetimePosition)
		: mveWindow{ mveWindow },
		spacetimePosition{ spacetimePosition},
		worldline{gameObject.getId(), spacetimePosition} {
		this->init(gameObject);
	}

	void TestObject::Action(GLFWwindow* window, double deltaTime) {

		spacetimePosition.set_g0(spacetimePosition.get_g0() + deltaTime);

		worldline.add(spacetimePosition);
	}

	ObjectDrawData TestObject::getDrawData(m4sta::mv observerPosition) {
		MvePhaseSpace P = this->worldline.get_pos_vel_on_PLC(observerPosition);
		return { P };
	}
}