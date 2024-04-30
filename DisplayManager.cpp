//
// Created by Cisco on 29/04/2024.
//

#include "DisplayManager.hpp"

void DisplayManager::CreateDisplay(const std::string& title, int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height,
        SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED);

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // SDL_CreateWindowAndRenderer(640*2, 480*2, SDL_WINDOW_OPENGL| SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED, &_window, &_renderer);

    SDL_RenderSetScale(_renderer, 2, 2);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    // SDL_SetRenderDrawColor(_renderer, rand(), rand(), rand(), 255);

}

void DisplayManager::Run()
{
    bool running = true;
    while(running)
    {

        // ParticleSystem particle_system;

        _particle_system.NewParticleSystem();

        _particle_system.DrawParticles(_renderer);

        // _particle_system.Update(_renderer);

        while(SDL_PollEvent(&_event))
        {
            if(_event.type == SDL_QUIT)
            {
                running = false;
            }
        }

        SDL_RenderPresent(_renderer);

    }

}

DisplayManager::~DisplayManager()
{
    SDL_DestroyWindow(_window);
    _window = nullptr;

    SDL_Quit();
}



