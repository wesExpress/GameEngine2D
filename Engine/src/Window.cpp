#include "Window.h"
#include "Event/KeyboardEvent.h"
#include "Event/WindowEvent.h"
#include "Event/MouseEvent.h"

static void SetGLFWErrorCallback(int error, const char* message)
{
    LOG_ERROR("GLFW Error ({0}): {1}", error, message);
}

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
            if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                LOG_INFO("GLAD initialized.");

                glfwSetWindowUserPointer(m_window, &m_windowData);

                // GLFW callbacks
                glfwSetErrorCallback(SetGLFWErrorCallback);
                SetKeyCallback();
                SetWindowCloseCallback();
                SetWindowResizeCallback();
                SetMouseButtonCallback();
                SetMouseMoveCallback();
                SetMouseScrollCallback();
            }
            else
            {
                LOG_ERROR("GLAD failed to initialze!");
            }
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
                KeyPressedEvent e(key);
                data.EventCallback(e);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent e(key);
                data.EventCallback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent e(key);
                data.EventCallback(e);
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
        WindowCloseEvent e;

        data.EventCallback(e);
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

        data.EventCallback(e);
    });
};

void Window::SetMouseButtonCallback()
{
    glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);

        switch(action)
        {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent e(button);
                data.EventCallback(e);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent e(button);
                data.EventCallback(e);
                break;
            }
        }
    });
};

void Window::SetMouseMoveCallback()
{
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
        MouseMovedEvent e(xPos, yPos);
        data.EventCallback(e);
    });
};

void Window::SetMouseScrollCallback()
{
    glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
    {
        WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent e(xOffset, yOffset);
        data.EventCallback(e);
    });
};