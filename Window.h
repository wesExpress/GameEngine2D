#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logging.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_TITLE "GLFW_WINDOW"

static void error_callback(int error, const char* description)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class Window
{
    public:
        Window()
        {
            m_width = DEFAULT_WINDOW_WIDTH;
            m_height = DEFAULT_WINDOW_HEIGHT;
            m_title = DEFAULT_WINDOW_TITLE;
        }
        Window(int width, int height, char* title)
        :
        m_width(width),
        m_height(height),
        m_title(title)
        {}

        ~Window()
        {
            LOG_ERROR("Destroying window.");
            glfwDestroyWindow(m_window);
        }

        bool InitWindow()
        {
            m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
            if (m_window == NULL)
            {
                LOG_ERROR("Window failed to initialize!");

                return false;
            }
            else
            {
                LOG_INFO("Window created.");

                glfwMakeContextCurrent(m_window);
                glfwSetKeyCallback(m_window, key_callback);

                return true;
            }
        }

        inline int GetWidth() const { return m_width; }
        inline int GetHeight() const { return m_height; }
        inline GLFWwindow* GetWindow() const { return m_window; }

    private:
        GLFWwindow* m_window = NULL;

        int m_width, m_height;
        char* m_title;
};

#endif