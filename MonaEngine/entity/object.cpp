#include "object.hpp"

namespace mve {
	TestObject::TestObject(MveWindow& mveWindow, MveGameObject& gameObject, m4sta::mv spacetimePosition)
		: mveWindow{ mveWindow },
		spacetimePosition{ spacetimePosition},
		worldline{gameObject.getId(), spacetimePosition} {
		this->init(gameObject);
	}

	void TestObject::Action(GLFWwindow* window, double deltaTime) {
		changeDirection(deltaTime);
		mv accel = getAcceleration(deltaTime);

		this->P.transform(accel, deltaTime);
		//spacetimePosition.set_g3(4.0);
		worldline.add(this->P.position);
	}

	m4sta::mv TestObject::getAcceleration(double deltaTime) {
		m4sta::mv ret = accelDirection * 0.1;
		return ret;
	}

	void TestObject::changeDirection(double deltaTime) {
		accelDirection.set_g1(sin(spacetimePosition.get_g0()));
		accelDirection.set_g2(cos(spacetimePosition.get_g0()));
	}

	ObjectDrawData TestObject::getDrawData(m4sta::mv observerPosition) {
		MvePhaseSpace P = this->worldline.get_pos_vel_on_PLC(observerPosition);
		return { P };
	}
}