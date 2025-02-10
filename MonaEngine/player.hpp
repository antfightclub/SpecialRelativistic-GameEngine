#pragma once

#include "relativity/Constants.hpp"
#include "relativity/math/Vector3.hpp"
#include "relativity/math/Vector4D.hpp"
#include "relativity/math/Matrix44.hpp"
#include "relativity/math/Quaternion.hpp"
#include "relativity/math/PhaseSpace.hpp"
#include "relativity/math/WorldLine.hpp"

#include "spacetimealgebra/m4sta.hpp"
#include "spacetimealgebra/mve_phasespace.hpp"
#include "spacetimealgebra/mve_worldline.hpp"


#include "mve_game_object.hpp"
#include "mve_model.hpp"

#include <iostream>

namespace mve {
	// Player entity
	struct PlayerDrawData {
		Math::Vector4D X;
		Math::Vector4D U;
		Math::Quaternion quaternion;
	};


	struct PlayerState {
		// Empty for now. For example, guns. Maybe.
	};

	struct GravitationData {
		double G;
		double massOfObject;
		m4sta::mv rapidityOfObject;
		m4sta::mv positionOfObject;
	};

	class Player {
	public:

		Player(MveWindow& mveWindow, MveGameObject& gameObject, mv pos, mv vel);

		MvePhaseSpace P;
		Math::Quaternion quaternion{ 1.0, 0.0, 0.0, 0.0 };
		double time = 0.0;
		MveWorldLine worldline;

		void Action(GLFWwindow* window, double deltaTime, GravitationData g);

		/// <summary>
		/// Returns the EnemyDrawData struct which just contains the enemy's X, U in the background frame as well as a rotation matrix.
		/// </summary>
		/// <param name="Xp">Player's spacetime coordinate</param>
		/// <param name="L">Lorentz boost to transform from the background frame to the player's frame</param>
		/// <param name="LL">Lorentz boost to transform from the player's frame to the background frame</param>
		

	private:
		MveWindow& mveWindow;
		MveGameObject::id_t id;
		double acceleration = 0.18;
		double resistivity = 0.20;
		double turnAcceleration = 9.0;
		double turnResistivity = 5.0;
		double turnSpeed1 = 0.0;
		double turnSpeed2 = 0.0;

		void init(GLFWwindow* window, mve::MveGameObject& gameObject) {	this->id = gameObject.getId(); }

		m4sta::mv getAcceleration(GLFWwindow* window, double deltaTime);
		m4sta::mv getAccelerationFromGravitation(GLFWwindow* window, double deltaTime, GravitationData g);
		// calc repulsion
		m4sta::mv p3CrossProduct(m4sta::mv& A, m4sta::mv& B);
		void changeDirection(GLFWwindow* window, double deltaTime);
		//getviscous

	};

}