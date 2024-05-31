//
// Created by Cisco on 31/05/2024.
//

#pragma once

#include "InputManager.hpp"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#ifdef _WIN32
#include <Windows.h>
#endif

#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <cstdlib>

namespace ParticleSystem
{
    class Scene;

    class Launcher
    {
    public:

        void                start();
        void                resetScene();
        void                toggleScenePause();
        void                updateViewport();
        void                centerWindow();
        void                toggleFullscreen();
        void                toggleUiVisibility();
        void                clearScreen() const;
        [[nodiscard]] auto  isMinimized() const -> bool;

        auto operator=(Launcher&&) -> Launcher& = delete;
        auto operator=(const Launcher&) -> Launcher& = delete;

                            Launcher(const Launcher&) = delete;
                            Launcher(Launcher&&) = delete;

                            Launcher();
                            ~Launcher();

    private:

        // Window variables

        GLFWwindow*             _window;

        int                     _windowWidth = 1280;
        int                     _windowHeight = 720;

        int                     _displayWidth;
        int                     _displayHeight;
        int                     _windowPosX;
        int                     _windowPosY;

        // Time
        float                   _fixedDeltaTime = 1.0F / 60.0F;

        // Pointer to the scene
        std::unique_ptr<Scene>  _scene;

        // Handlers
        void                    _handleInputs();
        void                    _handleUi(float deltaTime);
        void                    _updateGame(float deltaTime);
        void                    _updateScreen();

        // Mouse
        static void             _calculateMouseMovement(const double& xMouse, const double& yMouse, double& xMovement, double& yMovement);
        auto                    _projectMouse(const double& xMouse, const double& yMouse) -> glm::vec3;

        // Version getters
        static auto             _getOpenGLVendor()  -> std::string_view;
        static auto             _getOpenGLVersion() -> std::string_view;
        static auto             _getGLSLVersion()   -> std::string_view;
        static auto             _getGLFWVersion()   -> std::string;
        static auto             _getGladVersion()   -> std::string_view;
        static auto             _getImGuiVersion()  -> std::string;
        static auto             _getGLMVersion()    -> std::string;


    };

}
