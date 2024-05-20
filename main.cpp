#include <iostream>

#include "DisplayManager.hpp"

int main(int argc, char *argv[])
{
    GLFWwindow* window = nullptr;
    DisplayManager::InitGLFW();
    DisplayManager::CreateDisplay(window,640,480,"particle system!");

    while(true)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();

        if(glfwWindowShouldClose(window))//here is the error
        {
            DisplayManager::DestroyWindow(window);
            DisplayManager::EndGLFW();
            return 0;
        }
    }
    system("pause");

    return 0;
}
