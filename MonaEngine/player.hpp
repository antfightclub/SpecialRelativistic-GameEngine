#pragma once

#include "relativity/Constants.hpp"
#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"
#include "relativity/math/Matrix44.hpp"
#include "relativity/math/Quaternion.hpp"
#include "relativity/math/PhaseSpace.hpp"
#include "relativity/math/WorldLine.hpp"


#include "mve_game_object.hpp"
#include "mve_model.hpp"

#include <iostream>

namespace mve {
	// Player entity

	struct PlayerState {
		// Empty for now. For example, guns. Maybe.
	};

	class Player {
	public:

		Player(MveWindow& mveWindow, MveGameObject& gameObject, Math::Vector4D pos, Math::EntityState firstState);

		Math::PhaseSpace P;
		Math::Quaternion quaternion{ 1.0, 0.0, 0.0, 0.0 };
		double time = 0.0;
		Math::WorldLine worldline;

		void Action(GLFWwindow* window, double deltaTime);

	private:
		MveWindow& mveWindow;
		MveGameObject::id_t id;
		double acceleration = 1.8;
		double resistivity = 2.0;
		double turnAcceleration = 9.0;
		double turnResistivity = 5.0;
		double turnSpeed1 = 0.0;
		double turnSpeed2 = 0.0;

		void init(GLFWwindow* window, mve::MveGameObject& gameObject) {	this->id = gameObject.getId(); }

		Math::Vector4D getAcceleration(GLFWwindow* window, double deltaTime);
		// calc repulsion

		void changeDirection(GLFWwindow* window, double deltaTime);
		//getviscous

	};

}