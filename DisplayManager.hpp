//
// Created by Cisco on 29/04/2024.
//

#pragma once

#include "Particles.hpp"

#include <iostream>
#include <string>

#include <GL/freeglut.h>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_video.h>

class DisplayManager
{
public:

    void                CreateDisplay(const std::string& title, int width, int height);

    void                Run();

                        DisplayManager() = default;
                        ~DisplayManager();

private:

    SDL_Window*         _window = nullptr;
    SDL_Renderer*       _renderer = nullptr;
    SDL_Surface*        _window_surface = nullptr;
    SDL_Event           _event;

    ParticleParams      _params;
    ParticleSystem      _particle_system;


};
