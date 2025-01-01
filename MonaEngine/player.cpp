#include "player.hpp"

namespace SRGame {
	void Player::Action(GLFWwindow* window, double deltaTime) {
		changeDirection(window, deltaTime);

		Math::Vector4D acceleration = this->getAcceleration(window, deltaTime);
		this->P.transform(acceleration, deltaTime);
		this->time += deltaTime;
		Math::EntityState entityState{};
		this->worldline.add(P.X, entityState);
	}

	void Player::changeDirection(GLFWwindow* window, double deltaTime) {
		if (glfwGetKey(window, keyboardController.keys.turn_right) == GLFW_PRESS) {
			turnSpeed1 += this->turnAcceleration * deltaTime;
		}
		if (glfwGetKey(window, keyboardController.keys.turn_left) == GLFW_PRESS) {
			turnSpeed1 -= this->turnAcceleration * deltaTime;
		}

		if (glfwGetKey(window, keyboardController.keys.turn_up) == GLFW_PRESS) {
			turnSpeed2 -= this->turnAcceleration * deltaTime;
		}
		if (glfwGetKey(window, keyboardController.keys.turn_down) == GLFW_PRESS) {
			turnSpeed2 += this->turnAcceleration * deltaTime;
		}

		Math::Matrix44 mat = this->quaternion.getRotMat();
		this->quaternion *= Math::Quaternion{ this->turnSpeed1 * deltaTime, mat.getUp() };
		this->quaternion *= Math::Quaternion{ this->turnSpeed2 * deltaTime, mat.getRight() };
		this->turnSpeed1 -= this->turnResistivity * this->turnSpeed1 * deltaTime;
		this->turnSpeed2 -= this->turnResistivity * this->turnSpeed2 * deltaTime;
	}

	Math::Vector4D Player::getAcceleration(GLFWwindow* window, double deltaTime) {
		Math::Vector4D ac{};
		Math::Matrix44 rotationMatrix = this->quaternion.getRotMat();

		if (glfwGetKey(window, keyboardController.keys.accel_forward) == GLFW_PRESS) {
			ac = -Math::Vector4D{ 0.0, rotationMatrix.getForward() };
		}
		if (glfwGetKey(window, keyboardController.keys.accel_back) == GLFW_PRESS) {
			ac = Math::Vector4D{ 0.0, rotationMatrix.getForward() };
		}
		if (glfwGetKey(window, keyboardController.keys.accel_left) == GLFW_PRESS) {
			ac += Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		}
		if (glfwGetKey(window, keyboardController.keys.accel_right) == GLFW_PRESS) {
			ac -= Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		}
		ac.normalize();
		return ac;
	}
}