//
// Created by Cisco on 29/04/2024.
//

#include "Particles.hpp"


void ParticleSystem::NewParticleSystem()
{
    for(int i = 0; i < 100; i++)
    {
        auto* particle = new Particle({(float)rand(), (float)rand(), (float)rand(), 0, 0, 0, rand(), rand()%255, rand()%255, rand()%255, 255});
        _particles.emplace_back(particle);
    }

}

void ParticleSystem::DrawParticles()
{
    for(auto part : _particles)
    {
        // Blit image to entire window

    }
}

void ParticleSystem::Update()
{
    for(auto part : _particles)
    {

        // part->dx(rand()%640);
        // part->dy(rand()%480);
        //
        // part->x() += part->dx;
        // part->y() += part->dy;



    }
}

