//
// Created by Cisco on 29/04/2024.
//

#include "DisplayManager.hpp"

bool DisplayManager::InitGLFW()
{
    glfwSetErrorCallback(_error_callback);

    if (!glfwInit())
    {
        std::cerr << "glfw Initialization failed";
        return true;
    }
    return false;
}

bool DisplayManager::CreateDisplay(GLFWwindow* window, int width, int height, const std::string& title)
{

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (!window)
    {
        std::cerr << "Window or OpenGL context creation failed" << std::endl;
        glfwTerminate();
        return true;
    }

    // Set the required callback functions
    glfwSetKeyCallback(window, _key_callback);

    // Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error.
    //int version = gladLoadGL(glfwGetProcAddress);
    int version = gladLoadGL();
    if (version == 0)
    {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return true;
    }

    return false;

}

void DisplayManager::Run()
{
    while(!glfwWindowShouldClose(_window))
    {
        ParticleSystem particle_system;

        glfwSwapBuffers(_window);
        glfwPollEvents();


//        _particle_system.NewParticleSystem();

//        _particle_system.DrawParticles(_renderer);
//
//        _particle_system.Update(_renderer);
//

    }

}

void DisplayManager::DestroyWindow(GLFWwindow* window)
{
    glfwDestroyWindow(window);
}

void DisplayManager::EndGLFW()
{
    glfwTerminate();
}

DisplayManager::~DisplayManager()
{
    glfwTerminate();
    glfwDestroyWindow(_window);
    _window = nullptr;

}

void DisplayManager::_error_callback(int error, const char* description)
{
    std::cerr << "Error: %s\n" << description;
}

void DisplayManager::_key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}


