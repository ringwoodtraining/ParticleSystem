//
// Created by Cisco on 31/05/2024.
//

#include "Launcher.hpp"

using namespace ParticleSystem;

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}

Launcher::Launcher()
{
    glfwSetErrorCallback(glfw_error_callback);
    if(glfwInit() == 0)
        exit(1);

// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
    const char* glsl_version = "#version 430";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // 3.0+ only
#endif

    // According to init windowSize
    _displayWidth = _windowWidth;
    _displayHeight = _windowHeight;


    // Create window with graphics context
//    std::string windowTitle = PROJECT_NAME.data();
    std::string windowTitle = "Particle System";
    windowTitle += " (U to show/hide UI)";
    _window = glfwCreateWindow(_displayWidth, _displayHeight, windowTitle.c_str(), nullptr, nullptr);
    if (_window == nullptr)
        exit(1);
    glfwMakeContextCurrent(_window);
    //    glfwSwapInterval(1); // Enable vsync
    glfwSwapInterval(0); // Disable vsync
    //    glfwWindowHint(GLFW_REFRESH_RATE, 0); // Disable refresh rate
    //    glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE); // Disable refresh rate
    //    glfwWindowHint(GLFW_REFRESH_RATE, 60);

    // Callbacks
    glfwSetWindowUserPointer(_window, this);
    glfwSetKeyCallback(_window, InputManager::key_callback);

    

}
