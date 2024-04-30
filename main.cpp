#include <iostream>

#include "DisplayManager.hpp"

int main(int argc, char *argv[])
{
    DisplayManager MainDisplay;

    MainDisplay.CreateDisplay("Particle System", 800, 600);

    MainDisplay.Run();


    // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    // SDL_Rect rect;
    //
    // rect.w = 100;
    // rect.h = 100;
    //
    // rect.y = 0;
    // rect.x = 0;
    //
    // SDL_RenderDrawRect(renderer, &rect);
    // SDL_RenderDrawPoint(renderer, 640/2, 480/2);

    // std::vector<SDL_Point> v;
    //
    // for(int i = 0; i < 100; i++)
    //     v.push_back({rand()%640, rand()%480});
    //
    // SDL_RenderDrawPoints(renderer, v.data(), v.size());
    // SDL_RenderDrawLines(renderer, v.data(), v.size());
    //
    // SDL_RenderPresent(renderer);
    // SDL_Delay(3000);


    return 0;
}
