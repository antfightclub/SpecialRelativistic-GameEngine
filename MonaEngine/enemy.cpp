#include "enemy.hpp"

namespace mve {
	Enemy::Enemy(MveWindow& mveWindow, MveGameObject& gameObject, Math::Vector4D pos, Math::EntityState firstState) : mveWindow{ mveWindow }, P{ pos, Math::Vector4D{1.0, 0.0, 0.0, 0.0} }, worldline{gameObject.getId(), pos, firstState} {
		init(mveWindow.getGLFWwindow(), gameObject);
	}

	void Enemy::Action(GLFWwindow* window, double deltaTime) {
		changeDirection(window, deltaTime);

		Math::Vector4D acceleration = this->getAcceleration(window, deltaTime);

		this->P.transform(acceleration, deltaTime);

		Math::Quaternion quat = this->quaternion;

		Math::EntityState entityState{ quat };
		this->worldline.add(P.X, entityState);

	}

	Math::Vector4D Enemy::getAcceleration(GLFWwindow* window, double deltaTime) {
		return Math::Vector4D{ 1.0, -0.2, 0.0, 0.0 }; // Hardcoded for now, because why not.
	}
	

	void Enemy::changeDirection(GLFWwindow* window, double deltaTime) {
		//Math::Quaternion orientation = this->quaternion;

		//Math::Quaternion LeftRightRotation = Math::Quaternion{ this->turnSpeed1 * deltaTime, orientation.getRight() };
		//LeftRightRotation.normalize();
		//this->quaternion = LeftRightRotation * orientation;
		//this->quaternion.normalize();
	}

	EnemyDrawData Enemy::getDrawData(Math::Vector4D Xp, Math::Matrix44 L, Math::Matrix44 LL) {
		Math::PhaseSpace P = this->worldline.getXU_OnPLC(Xp); 
		Math::Quaternion q{};

		// Quaternion rotation as state on the worldline does not work for whatever reason.
		// The following was an attempt to get it to work, but it doesn't, so I've commented out the rotaty code above.
		if (P.X.getT() <= 0.0001 || P.X.getX() <= 0.0001 || P.X.getY() <= 0.0001 || P.X.getZ() <= 0.0001) {
			q = Math::Quaternion{ 1.0, 0.0, 0.0, 0.0 };
		}
		else {
			Math::StateOnPLC PLCState = this->worldline.getStateOnPLC();

			Math::Quaternion tmp1 = PLCState.state0.quaternion;
			Math::Quaternion tmp2 = PLCState.state1.quaternion;

			std::cout << "plcstate.state0.quaternion: " << tmp1.t << ", " << tmp1.x << ", " << tmp1.y << ", " << tmp1.z << "\n";
			std::cout << "plcstate.state1.quaternion: " << tmp2.t << ", " << tmp2.x << ", " << tmp2.y << ", " << tmp2.z << "\n";
			q = PLCState.state0.quaternion.getSphereP(PLCState.state1.quaternion, PLCState.sigma);
		}
	

		return {
			P.X, 
			P.U,
			q
		};
	}

}