#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

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

struct WindowProps
{
    WindowProps(unsigned int width = DEFAULT_WINDOW_WIDTH, 
    unsigned int height = DEFAULT_WINDOW_HEIGHT, 
    const std::string& title = DEFAULT_WINDOW_TITLE)
    :
    m_width(width),
    m_height(height),
    m_title(title)
    {}

    unsigned int m_width, m_height;
    std::string m_title;
};

class Window
{
    public:
        Window(const WindowProps& props);
        ~Window();

        bool InitWindow();

        inline int GetWidth() const { return m_windowProps.m_width; }
        inline int GetHeight() const { return m_windowProps.m_height; }
        inline GLFWwindow* GetWindow() const { return m_window; }

    private:
        GLFWwindow* m_window = NULL;

        int m_width, m_height;
        char* m_title;

        WindowProps m_windowProps;
};

#endif