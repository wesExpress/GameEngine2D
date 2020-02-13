#ifndef __WINDOWGLFW_H__
#define __WINDOWGLFW_H__

#include "Window.h"
#include "Event/Event.h"
#include "Rendering/RenderContext.h"

struct GLFWwindow;

namespace Engine
{
    class WindowGLFW : public Window
    {
        public:
            WindowGLFW(const WindowProps& props);
            virtual ~WindowGLFW();

            void Update() override;

            inline unsigned int GetWidth() const override { return m_windowData.width; }
            inline unsigned int GetHeight() const override { return m_windowData.height; }
            inline void* GetWindow() const override { return m_window; }

            void Destroy();
            inline void SetEventCallback(const std::function<void(Event&)>& callback) override { m_windowData.EventCallback = callback; }

        private:
            GLFWwindow* m_window = nullptr;
            WindowProps m_windowData;
            RenderContext* m_renderContext = nullptr;

            void Init(const WindowProps& props);

            void SetKeyCallback();
            void SetCharCallback();
            void SetWindowCloseCallback();
            void SetWindowResizeCallback();
            void SetMouseButtonCallback();
            void SetMouseMoveCallback();
            void SetMouseScrollCallback();
    };
}

#endif