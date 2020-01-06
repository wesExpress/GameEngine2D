#include "Window.h"
#include "KeyboardEvent.h"
#include "WindowEvent.h"

Window::Window()
{
    m_windowData = WindowProps();
}

Window::Window(const WindowProps& props)
:
m_windowData(props)
{}

Window::~Window()
{
    Destroy();
}

void Window::Create()
{    
    if (!glfwInit())
    {
        LOG_ERROR("GLFW failed to initialize!");
    }
    else
    {
        LOG_TRACE("GLFW initialized.");

        m_window = glfwCreateWindow(
        m_windowData.width, 
        m_windowData.height, 
        m_windowData.title.c_str(), NULL, NULL);

        if (m_window == NULL)
        {
            LOG_ERROR("Window failed to be created!");
        }
        else
        {
            LOG_INFO("Window created: {0}x{1}, {2}", 
            m_windowData.width, 
            m_windowData.height, 
            m_windowData.title);

            glfwMakeContextCurrent(m_window);
            glfwSetWindowUserPointer(m_window, &m_windowData);

            // GLFW callbacks
            SetKeyCallback();
            SetWindowCloseCallback();
            SetWindowResizeCallback();
        }
    }
}

void Window::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void Window::Destroy()
{
    LOG_ERROR("Destroying window.");
    glfwDestroyWindow(m_window);
    LOG_ERROR("Terminating GLFW");
    glfwTerminate();
}

void Window::SetKeyCallback()
{
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

        switch(action)
        {
            case GLFW_PRESS:
            {
                KeyPressedEvent e;
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent e;
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent e;
                break;
            }
        }
    });
}

void Window::SetWindowCloseCallback()
{
    glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
        WindowEvent e;
    });
};

void Window::SetWindowResizeCallback()
{
    glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
        data.width = width;
        data.height = height;

        WindowResizeEvent e(width, height);
    });
};