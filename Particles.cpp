//
// Created by Cisco on 29/04/2024.
//

#include "Particles.hpp"


void ParticleSystem::NewParticleSystem()
{
    for(int i = 0; i < 100; i++)
    {
        auto* particle = new Particle({rand()%640, rand()%480, 0, 0, 0, nullptr,rand()%255,rand()%255,rand()%255});
        _particles.emplace_back(particle);
    }

}

void ParticleSystem::DrawParticles(SDL_Renderer* renderer, SDL_Surface* surface)
{
    for(auto part : _particles)
    {
        // Blit image to entire window
        part->load("assets/rotating_orbs-1.0/PNG/32x32/rotating_orbs.png");
        SDL_BlitSurface( part->surface, nullptr, surface, nullptr);
        // SDL_SetRenderDrawColor(renderer, part->r, part->g, part->b, 255);
        // SDL_RenderDrawPoint(renderer, part->x, part->y);
    }
}

void ParticleSystem::Update(SDL_Renderer* renderer)
{
    for(auto part : _particles)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawPoint(renderer, part->x, part->y);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // part->dx(rand()%640);
        // part->dy(rand()%480);
        //
        // part->x() += part->dx;
        // part->y() += part->dy;



    }
}

