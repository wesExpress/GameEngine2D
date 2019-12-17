#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
    GLFWwindow* window = NULL;
    if (glfwInit())
    {
        window = glfwCreateWindow(640, 480, "GLFW Window", NULL, NULL);
        if (window == NULL)
        {
            std::cout << "Window creation failed." << std::endl;
            glfwTerminate();
        }
        else
        {
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
        std::cout << "GLFW could not be initialized." << std::endl;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}