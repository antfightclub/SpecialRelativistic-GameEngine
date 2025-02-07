#include "player.hpp"

namespace mve {

	Player::Player(MveWindow& mveWindow, MveGameObject& gameObject, mv pos, mv vel) : mveWindow{ mveWindow }, P{ MvePhaseSpace{pos, vel}}, worldline{gameObject.getId(), pos} {
		init(mveWindow.getGLFWwindow(), gameObject);
	}


	void Player::Action(GLFWwindow* window, double deltaTime) {
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

		mv acceleration = this->getAcceleration(window, deltaTime);
		std::cout << "accel = " << acceleration.toString() << std::endl;
		// Brake with regard to the background frame of reference (being the underlying world space grid).
		// This is not, you know, strictly very smart from a special relativity point of view.
		// But it's super helpful during development. In the future, it'd be great to implement
		// a way to match velocity with another object.
		if (mveWindow.k_state.k_brake == true) {
			acceleration -= this->P.getResist(resistivity * 20);
		}

		this->P.transform(acceleration, deltaTime);

		//this->time += deltaTime;
		//Math::EntityState entityState{this->quaternion}; // EntityState is defined in WorldLine.hpp, it only contains the orientation quaternion for now. Later it could include other things.
		this->worldline.add(P.position);
	}

	void Player::changeDirection(GLFWwindow* window, double deltaTime) {
		// This is pretty evil, but it works. Check the key state from the window, 
		// and then update turnspeed1 and turnspeed2 members depending on the turn priority.
		// Turn priority is set in the keystate depending on which key was last pressed.
		
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


		Math::Quaternion LeftRightRotation = Math::Quaternion{ this->turnSpeed1 * deltaTime, orientation.getUpward()};
		LeftRightRotation.normalize();
		this->quaternion = LeftRightRotation * orientation;

		orientation = this->quaternion;
		Math::Quaternion UpDownRotation = Math::Quaternion{ this->turnSpeed2 * deltaTime, orientation.getRight()};
		UpDownRotation.normalize();
		this->quaternion = UpDownRotation * orientation;
		this->quaternion.normalize();

		// This slowly stops rotation of the player; it's annoying if it keeps spinning
		this->turnSpeed1 -= this->turnResistivity * this->turnSpeed1 * deltaTime;
		this->turnSpeed2 -= this->turnResistivity * this->turnSpeed2 * deltaTime;
	}

	m4sta::mv Player::getAcceleration(GLFWwindow* window, double deltaTime) {
		int accel = mveWindow.k_state.k_accel; 
		//Math::Vector4D ac{};
		Math::Quaternion quatRot = this->quaternion;	
		mv ac{};

		mv forward{};
		forward.set_g1(quatRot.getForward().getX());
		forward.set_g2(quatRot.getForward().getY());
		forward.set_g3(quatRot.getForward().getZ());

		mv right{};
		right.set_g1(quatRot.getRight().getX());
		right.set_g2(quatRot.getRight().getY());
		right.set_g3(quatRot.getRight().getZ());

		mv upward{};
		upward.set_g1(quatRot.getUpward().getX());
		upward.set_g2(quatRot.getUpward().getY());
		upward.set_g3(quatRot.getUpward().getZ());

		// Evil 
		// Either forwards or backwards
		if (accel & 1) {
			//ac = Math::Vector4D{ 0.0, quatRot.getForward() };
			ac = forward;
		}
		else if (accel & 2) {
			//ac = -Math::Vector4D{ 0.0, quatRot.getForward() };
			ac = -forward;
		}
		else {
			//ac = Math::Vector4D{};
			// no change
		}

		// Left and right
		if (mveWindow.k_state.k_accel_priority == 0) { // Right is priority
			if (accel & 4) {
				//ac += Math::Vector4D{ 0.0, quatRot.getRight() };
				ac += right;
			}
			else if (accel & 8) {
				//ac -= Math::Vector4D{ 0.0, quatRot.getRight() };
				ac -= right;
			}
		}
		else if (mveWindow.k_state.k_accel_priority == 1) { // Left is priority
			if (accel & 8) {
				//ac -= Math::Vector4D{ 0.0, quatRot.getRight() };
				ac -= right;
			}
			else if (accel & 4) {
				//ac += Math::Vector4D{ 0.0, quatRot.getRight() };
				ac += right;
			}
		}

		else if (mveWindow.k_state.k_accel_priority == 2) { // Up is priority
			if (accel & 16) {
				//ac -= Math::Vector4D{ 0.0, quatRot.getUpward() };
				ac -= upward;
			}
			else if (accel & 32) {
				//ac += Math::Vector4D{ 0.0, quatRot.getUpward() };
				ac += upward;
			}
		}
		else if (mveWindow.k_state.k_accel_priority == 3) { // Down is priority
			if (accel & 32) {
				//ac += Math::Vector4D{ 0.0, quatRot.getUpward() };
				ac += upward;
			}
			else if (accel & 16) {
				//ac -= Math::Vector4D{ 0.0, quatRot.getUpward() };
				ac -= upward;
			}
		}

		ac = unit(ac);

		//ac.normalize();
		return ac;
	}

	/*
	PlayerDrawData Player::getDrawData(mv Xp, Math::Matrix44 L, Math::Matrix44 LL) {
		MvePhaseSpace P = this->worldline.get_pos_vel_on_PLC(Xp);
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
	}*/

}