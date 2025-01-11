#include "player.hpp"

namespace mve {

	Player::Player(MveWindow& mveWindow, MveGameObject& gameObject, Math::Vector4D pos, Math::EntityState firstState) : mveWindow{ mveWindow }, P{ Math::PhaseSpace{pos, Math::Vector4D(1.0, 0.0, 0.0, 0.0)} }, worldline{ gameObject.getId(), pos, firstState } {
		init(mveWindow.getGLFWwindow(), gameObject);
	}


	void Player::Action(GLFWwindow* window, double deltaTime) {
		//updateKeyMap(window);

				// Print keymap state
		/*std::cout << "***** EVIL KEYMAP STATE *****\n"
			<< "k_accel " << mveWindow.k_state.k_accel << '\n'
			<< "k_accel_priority " << mveWindow.k_state.k_accel_priority << '\n'
			<< "k_turn_right " << mveWindow.k_state.k_turn_right << '\n'
			<< "k_turn_left " << mveWindow.k_state.k_turn_left << '\n'
			<< "k_turn_up " << mveWindow.k_state.k_turn_up << '\n'
			<< "k_turn_down " << mveWindow.k_state.k_turn_down << '\n'
			<< "k_turn_priority_1 " << mveWindow.k_state.k_turn_priority_1 << '\n'
			<< "k_turn_priority_2 " << mveWindow.k_state.k_turn_priority_2 << '\n'
			<< "k_brake " << mveWindow.k_state.k_brake << '\n';*/

		changeDirection(window, deltaTime);

		Math::Vector4D acceleration = this->getAcceleration(window, deltaTime);

		// Brake with regard to the background frame of reference (being the underlying world space grid)
		// This is not, you know, strictly very smart from a special relativity point of view
		if (mveWindow.k_state.k_brake == true) {
			acceleration -= this->P.getResist(resistivity * 20);
		}

		this->P.transform(acceleration, deltaTime);

		this->time += deltaTime;
		Math::EntityState entityState{};
		this->worldline.add(P.X, entityState);
	}

	void Player::changeDirection(GLFWwindow* window, double deltaTime) {


		// Evil
		if (mveWindow.k_state.k_turn_priority_1 == 0) {
			if (mveWindow.k_state.k_turn_right) {
				this->turnSpeed1 += this->turnAcceleration * deltaTime;
			}
			else if (mveWindow.k_state.k_turn_left) {
				this->turnSpeed1 -= this->turnAcceleration * deltaTime;
			}
		}
		else {
			if (mveWindow.k_state.k_turn_left) {
				this->turnSpeed1 -= this->turnAcceleration * deltaTime;
			}
			else if (mveWindow.k_state.k_turn_right) {
				this->turnSpeed1 += this->turnAcceleration * deltaTime;
			}
		}

		if (mveWindow.k_state.k_turn_priority_2 == 0) {
			if (mveWindow.k_state.k_turn_up) {
				this->turnSpeed2 -= this->turnAcceleration * deltaTime;
			}
			else if (mveWindow.k_state.k_turn_down) {
				this->turnSpeed2 += this->turnAcceleration * deltaTime;
			}
		}
		else {
			if (mveWindow.k_state.k_turn_down) {
				this->turnSpeed2 += this->turnAcceleration * deltaTime;
			}
			else if (mveWindow.k_state.k_turn_up) {
				this->turnSpeed2 -= this->turnAcceleration * deltaTime;
			}
		}

		
		Math::Matrix44 mat = this->quaternion.getRotMat();
		Math::Quaternion orientation = this->quaternion;
	/*	std::cout << "*********** QUAT DEBUG ********\n";
		double length = std::sqrt(this->quaternion.t* this->quaternion.t + this->quaternion.x* this->quaternion.x + this->quaternion.y * this->quaternion.y + this->quaternion.z* this->quaternion.z);
		std::cout << "Player::quaternion length = " << length << "\n";
		std::cout << "Player::changeDirection rotmat from quat:" << mat << '\n';

		std::cout << "mat.getUp().getNormalize() " << mat.getUp().getNormalize() << '\n';
		std::cout << "mat.getRight().getNormalize() " << mat.getRight().getNormalize() << '\n';

		Math::Vector3 vec = mat.getUp().getNormalize();
		
		double dotUpRight = vec.dot(mat.getRight().getNormalize());
		double dotUpForward = vec.dot(mat.getForward().getNormalize());


		std::cout << "dot between up and right " << dotUpRight << "\n";
		std::cout << "dot between up and forward " << dotUpForward << "\n";
		

		std::cout << "*********** END QUAT DEBUG *********\n";*/

		//Math::Quaternion quatcopy = this->quaternion;
		//glm::mat4 mat = glm::toMat4(this->quaternion);
		//glm::quat copy = this->quaternion;
		/*Math::Quaternion copy = this->quaternion;
		Math::Vector3 up = copy.getUpward().getNormalize();
		Math::Vector3 right = copy.getRight().getNormalize();*/

		//this->quaternion = this->quaternion * Math::Quaternion{ this->turnSpeed1 * deltaTime, mat.getUp()};
		//this->quaternion.normalize();
		//this->quaternion = Math::Quaternion{ this->turnSpeed2 * deltaTime, mat.getRight()} *this->quaternion;
		//this->quaternion.normalize();

		Math::Quaternion LeftRightRotation = Math::Quaternion{ this->turnSpeed1 * deltaTime, orientation.getUpward()};
		LeftRightRotation.normalize();
		this->quaternion = LeftRightRotation * orientation;

		orientation = this->quaternion;
		Math::Quaternion UpDownRotation = Math::Quaternion{ this->turnSpeed2 * deltaTime, orientation.getRight()};
		UpDownRotation.normalize();
		this->quaternion = UpDownRotation * orientation;
		this->quaternion.normalize();


		this->turnSpeed1 -= this->turnResistivity * this->turnSpeed1 * deltaTime;
		this->turnSpeed2 -= this->turnResistivity * this->turnSpeed2 * deltaTime;
	}

	Math::Vector4D Player::getAcceleration(GLFWwindow* window, double deltaTime) {
		int accel = mveWindow.k_state.k_accel;
		Math::Vector4D ac{};
		//Math::Matrix44 rotationMatrix = this->quaternion.getRotMat();
		Math::Quaternion quatRot = this->quaternion;		

		//// Evil 
		//if (accel & 1) {
		//	ac = -Math::Vector4D{ 0.0, rotationMatrix.getForward() };
		//}
		//else if (accel & 2) {
		//	ac = Math::Vector4D{ 0.0, rotationMatrix.getForward() };
		//}
		//else {
		//	ac = Math::Vector4D{};
		//}

		//if (mveWindow.k_state.k_accel_priority == 0) {
		//	if (accel & 4) {
		//		ac += Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		//	}
		//	else if (accel & 8) {
		//		ac -= Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		//	}
		//}
		//else {
		//	if (accel & 8) {
		//		ac -= Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		//	}
		//	else if (accel & 4) {
		//		ac += Math::Vector4D{ 0.0, rotationMatrix.getRight() };
		//	}
		//}

		// Evil 
		// Either forwards or backwards
		if (accel & 1) {
			ac = Math::Vector4D{ 0.0, quatRot.getForward() };
		}
		else if (accel & 2) {
			ac = -Math::Vector4D{ 0.0, quatRot.getForward() };
		}
		else {
			ac = Math::Vector4D{};
		}

		// Left and right
		if (mveWindow.k_state.k_accel_priority == 0) { // Right is priority
			if (accel & 4) {
				ac += Math::Vector4D{ 0.0, quatRot.getRight() };
			}
			else if (accel & 8) {
				ac -= Math::Vector4D{ 0.0, quatRot.getRight() };
			}
		}
		else if (mveWindow.k_state.k_accel_priority == 1) { // Left is priority
			if (accel & 8) {
				ac -= Math::Vector4D{ 0.0, quatRot.getRight() };
			}
			else if (accel & 4) {
				ac += Math::Vector4D{ 0.0, quatRot.getRight() };
			}
		}

		else if (mveWindow.k_state.k_accel_priority == 2) { // Up is priority
			if (accel & 16) {
				ac -= Math::Vector4D{ 0.0, quatRot.getUpward() };
			}
			else if (accel & 32) {
				ac += Math::Vector4D{ 0.0, quatRot.getUpward() };
			}
		}
		else if (mveWindow.k_state.k_accel_priority == 3) { // Down is priority
			if (accel & 32) {
				ac += Math::Vector4D{ 0.0, quatRot.getUpward() };
			}
			else if (accel & 16) {
				ac -= Math::Vector4D{ 0.0, quatRot.getUpward() };
			}
		}

		ac.normalize();
		return ac;
	}
}