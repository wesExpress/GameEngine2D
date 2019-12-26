#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Logging.h"
#include "Window.h"

int main(void)
{
    Log::Init();
    Window gameWindow = Window(WindowProps());
    if (glfwInit())
    {
        if (gameWindow.Init())
        {
            while (!glfwWindowShouldClose(gameWindow.GetWindow()))
            {
                glfwPollEvents();
            }
        }
        else
        {
            LOG_ERROR("Terminating glfw.");
            glfwTerminate();
        }
    }
    else
    {
        LOG_ERROR("GLFW could not be initialized.");
        glfwTerminate();
    }
    
    return 0;
}