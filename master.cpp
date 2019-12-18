#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Logging.h"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    Log::Init();
    GLFWwindow* window = NULL;
    if (glfwInit())
    {
        window = glfwCreateWindow(640, 480, "GLFW Window", NULL, NULL);
        if (window == NULL)
        {
            LOG_ERROR("Window creation failed.");
            glfwTerminate();
        }
        else
        {
            LOG_INFO("Window created.");

            glfwSetKeyCallback(window, key_callback);
            glfwMakeContextCurrent(window);

            while (!glfwWindowShouldClose(window))
            {
                glfwPollEvents();
            }
        }
    }
    else
    {
        LOG_ERROR("GLFW could not be initialized.");
    }

    glfwDestroyWindow(window);
    LOG_ERROR("Window destroyed.");
    glfwTerminate();
    
    return 0;
}