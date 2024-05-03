//
// Created by Cisco on 29/04/2024.
//

#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>

#define SDL_MAIN_HANDLED
#include <SDL_render.h>
#include <SDL_image.h>

struct Particle
{
    // Initial position
    int x = 0;
    int y = 0;

    // Delta position
    int dx = 0;
    int dy = 0;

    // Speed
    int velocity = 0;

    // Texture
    SDL_Surface* surface = nullptr;

    bool load(const std::string& file)
    {
        //The final optimized image
        SDL_Surface* optimizedSurface = nullptr;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load(file.c_str());
        if(loadedSurface == nullptr)
        {
            printf( "Unable to load image %s! SDL_image Error: %s\n", file.c_str(), IMG_GetError() );
        }
        else
        {
            //Convert surface to screen format
            optimizedSurface = SDL_ConvertSurface( loadedSurface, surface->format, 0 );
            if( optimizedSurface == nullptr )
            {
                printf( "Unable to optimize image %s! SDL Error: %s\n", file.c_str(), SDL_GetError() );
            }

            //Get rid of old loaded surface
            SDL_FreeSurface(loadedSurface);
        }

        return optimizedSurface;
    }

    // Color
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;

};

struct ParticleParams
{
    // Maxium amount of particles
    const int MAX_PARTICLES = 10000;
    // Maxium life span
    const int MAX_LIFESPAN = 3000;

    // World gravity
    const float GRAVITY = 9.81;

};

class ParticleSystem final
{
public:

    void                    NewParticleSystem();
    void                    DrawParticles(SDL_Renderer* renderer, SDL_Surface* surface);
    void                    Update(SDL_Renderer* renderer);

    ParticleSystem() = default;
    explicit                ParticleSystem(const ParticleParams params) : _params(params) {}
    virtual                 ~ParticleSystem() = default;

private:

    ParticleParams          _params;
    std::time_t             _result = std::time(nullptr);
    std::vector<Particle*>  _particles;


};

