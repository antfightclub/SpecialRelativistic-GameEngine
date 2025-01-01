#pragma once

#include "mve_game_object.hpp"
#include "mve_window.hpp"

namespace mve {
	class KeyboardInputController {
    public:
        struct KeyMappings {
           /* int moveLeft = GLFW_KEY_A;
            int moveRight = GLFW_KEY_D;
            int moveForward = GLFW_KEY_W;
            int moveBackward = GLFW_KEY_S;
            int moveUp = GLFW_KEY_E;
            int moveDown = GLFW_KEY_Q;
            int lookLeft = GLFW_KEY_LEFT;
            int lookRight = GLFW_KEY_RIGHT;
            int lookUp = GLFW_KEY_UP;
            int lookDown = GLFW_KEY_DOWN;*/

            // acceleration
            int accel_forward   = GLFW_KEY_W;
            int accel_back = GLFW_KEY_S;
            int accel_right = GLFW_KEY_D;
            int accel_left = GLFW_KEY_A;
            int brake = GLFW_KEY_R;
            
            // turning
            int turn_right = GLFW_KEY_RIGHT;
            int turn_left = GLFW_KEY_LEFT;
            int turn_up = GLFW_KEY_UP;
            int turn_down = GLFW_KEY_DOWN;

        };
        
        //glm::vec3 moveInPlaneXZ(GLFWwindow* window, float dt, MveGameObject &gameObject);
        
        KeyMappings keys{};
        float moveSpeed{ 0.002f };
        float lookSpeed{ 0.002f };

	};

}