#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GLFW/glfw3.h>
#include <string>

#include "Logging.h"
#include "Event/Event.h"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define DEFAULT_WINDOW_TITLE "GLFW_WINDOW"

struct WindowProps
{
    WindowProps(unsigned int width = DEFAULT_WINDOW_WIDTH, 
    unsigned int height = DEFAULT_WINDOW_HEIGHT, 
    const char* title = DEFAULT_WINDOW_TITLE)
    :
    width(width),
    height(height),
    title(title)
    {}

    WindowProps(const WindowProps& other)
    :
    width(other.width),
    height(other.height),
    title(other.title)
    {}

    unsigned int width, height;
    std::string title;
    std::function<void(Event&)> EventCallback;
};

class Window
{
    public:
        Window();
        Window(const WindowProps& props);
        ~Window();

        void Create();
        void Update();
        void Destroy();

        inline int GetWidth() const { return m_windowData.width; }
        inline int GetHeight() const { return m_windowData.height; }
        inline GLFWwindow* GetWindow() const { return m_window; }

        inline void SetEventCallback(const std::function<void(Event&)>& callback) { m_windowData.EventCallback = callback; }

    private:
        GLFWwindow* m_window = NULL;
        WindowProps m_windowData;

        void SetKeyCallback();
        void SetWindowCloseCallback();
        void SetWindowResizeCallback();
        void SetMouseButtonCallback();
        void SetMouseMoveCallback();
        void SetMouseScrollCallback();
};

#endif