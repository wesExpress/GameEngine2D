#ifndef __ENGINEAPP_H__
#define __ENGINEAPP_H__

#include "Window.h"

#include "Engine/Layer.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"
#include "Engine/EngineDefines.h"

#include "Event/Event.h"
#include "Event/WindowEvent.h"

namespace Engine
{
    class EngineApp
    {
        public:
            EngineApp();

            void Run();
            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);

            inline Window& GetWindow() const { return *m_window; }
            static EngineApp& Get() {return *m_instance; };

        private:
            bool OnWindowCloseEvent(WindowCloseEvent& e);
            bool OnWindowResizeEvent(WindowResizeEvent& e);

            bool m_isRunning = true;
            bool m_isMinimized = false;

            ImGuiLayer* m_imguiLayer = nullptr;
            Scope<Window> m_window;
            LayerStack m_layerStack;

            static EngineApp* m_instance;

            float m_lastTime = 0.0f;
    };

    EngineApp* CreateApplication();
}
#endif
