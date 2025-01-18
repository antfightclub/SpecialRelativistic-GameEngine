#include "enemy.hpp"

namespace mve {
	Enemy::Enemy(MveWindow& mveWindow, MveGameObject& gameObject, Math::Vector4D pos, Math::EntityState firstState) : mveWindow{ mveWindow }, P{ pos, Math::Vector4D{1.0, 0.0, 0.0, 0.0} }, worldline{gameObject.getId(), pos, firstState} {
		init(mveWindow.getGLFWwindow(), gameObject);
	}

	void Enemy::Action(GLFWwindow* window, double deltaTime) {
		changeDirection(window, deltaTime);

		Math::Vector4D acceleration = this->getAcceleration(window, deltaTime);

		this->P.transform(acceleration, deltaTime);

		Math::EntityState entityState{ this->quaternion };
		this->worldline.add(P.X, entityState);

	}

	Math::Vector4D Enemy::getAcceleration(GLFWwindow* window, double deltaTime) {
		return Math::Vector4D{ 1.0, 0.2, 0.2, 0.2 }; // Hardcoded for now, because why not.
	}
	

	void Enemy::changeDirection(GLFWwindow* window, double deltaTime) {

	}

	EnemyDrawData Enemy::getDrawData(Math::Vector4D Xp, Math::Matrix44 L, Math::Matrix44 LL) {
		Math::PhaseSpace P = worldline.getXU_OnPLC(Xp); 
		Math::StateOnPLC PLCState = worldline.getStateOnPLC();
		Math::Quaternion q = PLCState.state0.quaternion.getSphereP(PLCState.state1.quaternion, PLCState.sigma);
		Math::Matrix44 R = q.getRotMat();
		return {
			P.X, 
			P.U,
			R
		};
	}

}