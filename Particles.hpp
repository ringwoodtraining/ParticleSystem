//
// Created by Cisco on 29/04/2024.
//

#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>


struct Particle
{
    // Initial position
    float x = 0;
    float y = 0;
    float z = 0;


    // Delta position
    int dx = 0;
    int dy = 0;
    int dz = 0;

    // Speed
    int velocity = 0;


    // Color
    int r = 0;
    int g = 0;
    int b = 0;
    int a = 255;

};

struct ParticleParams
{
    // Maximum amount of particles
    const int MAX_PARTICLES = 10000;
    // Maximum life span
    const int MAX_LIFESPAN = 3000;

    // World gravity
    const float GRAVITY = 9.81;

};

class ParticleSystem final
{
public:

    void                    NewParticleSystem();
    void                    DrawParticles();
    void                    Update();

    explicit                ParticleSystem(const ParticleParams params) : _params(params) {}
                            ParticleSystem() = default;
    virtual                 ~ParticleSystem() = default;

private:

    ParticleParams          _params;
    std::time_t             _result = std::time(nullptr);
    std::vector<Particle*>  _particles;


};

