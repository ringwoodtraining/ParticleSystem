//
// Created by Cisco on 31/05/2024.
//

#pragma once

#include "Launcher.hpp"

struct GLFWwindow;

namespace ParticleSystem
{

    class InputManager
    {
    public:
        //Callback function for key window events
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        //Functions to check if a key is pressed (used for each game loop iteration)
        static auto isForwardKeyPressed(GLFWwindow* window) -> bool;
        static auto isBackwardKeyPressed(GLFWwindow* window) -> bool;
        static auto isLeftKeyPressed(GLFWwindow* window) -> bool;
        static auto isRightKeyPressed(GLFWwindow* window) -> bool;
        static auto isUpKeyPressed(GLFWwindow* window) -> bool;
        static auto isDownKeyPressed(GLFWwindow* window) -> bool;

        //Functions for mouse movement (used for each game loop iteration)
        static void getMousePosition(GLFWwindow* window, double& xPos, double& yPos);
        static auto isKeyMouseMovementPressed(GLFWwindow* window) -> bool;
        static auto isKeyMouseSetAttractorPressed(GLFWwindow* window) -> bool;

    private:

    };

} // ParticleSystem

