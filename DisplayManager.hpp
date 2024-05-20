//
// Created by Cisco on 29/04/2024.
//

#pragma once

#include "Particles.hpp"

#include <iostream>
#include <string>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

class DisplayManager
{
public:

    static bool         InitGLFW();
    static bool         CreateDisplay(GLFWwindow* window, int width, int height, const std::string& title);

    void                Run();

    static void         EndGLFW();
    static void         DestroyWindow(GLFWwindow* window);


                        DisplayManager() = default;
                        ~DisplayManager();

private:

    GLFWwindow*         _window;

    ParticleParams      _params;
    ParticleSystem      _particle_system;

    static void         _error_callback(int error, const char* description);
    static void         _key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


};
