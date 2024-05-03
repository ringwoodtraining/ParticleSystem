cmake_minimum_required(VERSION 3.28)
project(ParticleSystem)

set(CMAKE_CXX_STANDARD 17)

#SDL
add_subdirectory(SDL-release-2.30.2/)
include_directories(SDL-release-2.30.2/include)
#SDL_image
add_subdirectory(SDL_image-release-2.8.2)
include_directories(SDL_image-release-2.8.2/include)

add_subdirectory(freeglut-3.4.0)
include_directories(freeglut-3.4.0/include)


set(HEADER_FILES DisplayManager.hpp)

set(SOURCE_FILES DisplayManager.cpp
        Particles.cpp
        Particles.hpp)

add_executable(ParticleSystem main.cpp ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(ParticleSystem SDL2 SDL2_image -static)