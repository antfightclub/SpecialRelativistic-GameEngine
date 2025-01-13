#pragma once

namespace mve {
	class KeyboardInputController {
    public:
        struct KeyMappings {
            // acceleration
            int accel_forward   = GLFW_KEY_W;
            int accel_back = GLFW_KEY_S;
            int accel_right = GLFW_KEY_D;
            int accel_left = GLFW_KEY_A;
            int accel_up = GLFW_KEY_SPACE;
            int accel_down = GLFW_KEY_LEFT_SHIFT;
            int brake = GLFW_KEY_R; // Kills all velocity, mostly for debug purposes
                        
            // turning
            int turn_right = GLFW_KEY_RIGHT;
            int turn_left = GLFW_KEY_LEFT;
            int turn_up = GLFW_KEY_UP;
            int turn_down = GLFW_KEY_DOWN;

        };
                
        KeyMappings keys{};

	};

}