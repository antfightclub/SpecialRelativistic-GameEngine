#pragma once

#include "relativity/Constants.hpp"
#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"
#include "relativity/math/Matrix44.hpp"
#include "relativity/math/Quaternion.hpp"
#include "relativity/math/PhaseSpace.hpp"
#include "relativity/math/WorldLine.hpp"
#include "keyboard_movement_controller.hpp"

#include "mve_game_object.hpp"
#include "mve_model.hpp"

namespace SRGame {
	// Player entity

	struct PlayerState {
		// Empty for now. For example, guns. Maybe.
	};


	class Player {
	public:

		Player(mve::MveGameObject& gameObject, Math::Vector4D pos, Math::EntityState firstState) : P{ pos, Math::Vector4D(1.0, 0.0, 0.0, 0.0) }, worldline{ gameObject.getId(), pos, firstState } {
			init(gameObject);
		}

		Math::PhaseSpace P;
		Math::Quaternion quaternion{1.0, 0.0, 0.0, 0.0};
		double time = 0.0;
		Math::WorldLine worldline;
		mve::KeyboardInputController keyboardController{};
		
		void Action(GLFWwindow* window, double deltaTime);


	private:
		mve::MveGameObject::id_t id; 
		double acceleration = 1.8;
		double resistivity = 2.0;
		double turnAcceleration = 9.0;
		double turnResistivity = 5.0;
		double turnSpeed1 = 0.0;
		double turnSpeed2 = 0.0;

		// Accel and turn priorities??

		

		void init(mve::MveGameObject& gameObject){
			this->id = gameObject.getId();
		}

		Math::Vector4D getAcceleration(GLFWwindow* window, double deltaTime);
		// calc repulsion
		
		void changeDirection(GLFWwindow* window, double deltaTime);
		//getviscous

		
	};
}