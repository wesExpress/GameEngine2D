#include "Window.h"

Window::Window(const WindowProps& props)
:
m_windowData(props)
{}

Window::~Window()
{
    LOG_ERROR("Destroying window.");
    glfwDestroyWindow(m_window);
}

bool Window::Init()
{
    m_window = glfwCreateWindow(
        m_windowData.width, 
        m_windowData.height, 
        m_windowData.title.c_str(), NULL, NULL);

    if (m_window == NULL)
    {
        LOG_ERROR("Window failed to initialize!");

        return false;
    }
    else
    {
        LOG_INFO("Window created: {0}x{1}, {2}", 
        m_windowData.width, 
        m_windowData.height, 
        m_windowData.title);

        glfwMakeContextCurrent(m_window);
        glfwSetKeyCallback(m_window, key_callback);

        //glfwSetWindowUserPointer(m_window, &m_windowProps);

        //glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
        //{
        //    WindowProps& props = *(WindowProps*)glfwGetWindowUserPointer(window);
        //}
        //);

        return true;
    }
}