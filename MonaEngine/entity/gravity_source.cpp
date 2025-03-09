#include "gravity_source.hpp"

namespace mve {
	GravitySource::GravitySource(MveWindow& mveWindow, MveGameObject& gameObject, double mass, m4sta::mv position, m4sta::mv rapidity)
		: mveWindow{ mveWindow },
		mass{mass},
		position{position},
		rapidity{rapidity},
		worldline{gameObject.getId(), position}
	{
		this->init(gameObject);
	}

	void GravitySource::Action(GLFWwindow* window, double deltaTime) {
		// Works for now, since it is not moving yet
		position.set_g0(position.get_g0() + deltaTime);
		worldline.add(position);
	}

	MvePhaseSpace GravitySource::getDrawData(m4sta::mv observerPosition) {
		return this->worldline.get_pos_vel_on_PLC(observerPosition);
	}

}