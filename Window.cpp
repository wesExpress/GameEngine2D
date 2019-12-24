#include "Window.h"

Window::Window(const WindowProps& props)
{
    m_windowProps.m_width = props.m_width;
    m_windowProps.m_height = props.m_height;
    m_windowProps.m_title = props.m_title;
}

Window::~Window()
{
    LOG_ERROR("Destroying window.");
    glfwDestroyWindow(m_window);
}

bool Window::InitWindow()
{
    m_window = glfwCreateWindow(
        m_windowProps.m_width, 
        m_windowProps.m_height, 
        m_windowProps.m_title.c_str(), NULL, NULL);
        
    if (m_window == NULL)
    {
        LOG_ERROR("Window failed to initialize!");

        return false;
    }
    else
    {
        LOG_INFO("Window created: {0}, {1}, {2}", 
        m_windowProps.m_width, 
        m_windowProps.m_height, 
        m_windowProps.m_title);

        glfwMakeContextCurrent(m_window);
        glfwSetKeyCallback(m_window, key_callback);

        return true;
    }
}