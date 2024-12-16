#pragma once

#include "mve_model.hpp"

#include <memory>

namespace mve {

	struct Transform2DComponent {
		glm::vec2 translation{}; // (position offset) 
		glm::vec2 scale{ 1.f, 1.f };
		float rotation;

		glm::mat2 mat2() {
			const float s = glm::sin(rotation);
			const float c = glm::cos(rotation);
			glm::mat2 rotMatrix{ {c, s}, {-s, c} };
			glm::mat2 scaleMatrix{ {scale.x, 0.0f}, {0.0f, scale.y} };
			return rotMatrix*scaleMatrix;
		} // returns 2x2 identity matrix
	}; 
	
	class MveGameObject {
	public:
		using id_t = unsigned int;
		
		static MveGameObject createGameObject() {
			static id_t currentId = 0;
			return MveGameObject{ currentId++ };
		}

		MveGameObject(const MveGameObject&) = delete;
		MveGameObject& operator=(const MveGameObject&) = delete;
		MveGameObject(MveGameObject&&) = default;
		MveGameObject& operator=(MveGameObject&&) = default;

		const id_t getId() { return id; }

		std::shared_ptr<MveModel> model{};
		glm::vec3 color{};
		Transform2DComponent transform2D{};

	private:
		MveGameObject(id_t objId) : id{objId} {}

		id_t id;
	
	};
}