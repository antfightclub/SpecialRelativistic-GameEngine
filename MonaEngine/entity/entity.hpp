#pragma once

namespace mve {
	struct Entity {
		virtual void Action() = 0; // pure virtual function
		virtual ~Entity() {}     // ensure derived destructors are virtual
	};
}