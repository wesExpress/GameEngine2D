#include "EngineApp.h"
#include "Event/WindowEvent.h"
#include "Input.h"
#include "EngineDefines.h"
#include "Platform/GLFW/TimeGLFW.h"
#include "Timestep.h"

namespace Engine
{
    EngineApp* EngineApp::m_instance = nullptr;

    EngineApp::EngineApp()
    {   
        ENGINE_ASSERT(!m_instance, "App already exists!");
        m_instance = this;

        m_window = Scope<Window>(Window::Create());
        m_window->SetEventCallback(BIND_FN(EngineApp::OnEvent));
        m_window->SetVsync(false);

        m_imguiLayer = new ImGuiLayer();
        PushOverlay(m_imguiLayer);
    }

    void EngineApp::Run()
    {
        while(m_isRunning)
        {
            float time = GetTime();
            Timestep timestep = time - m_lastTime;
            m_lastTime = time;

            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_imguiLayer->Begin();
            for (Layer* layer : m_layerStack)
            {
                layer->OnImGuiRender();
            }
            m_imguiLayer->End();

            m_window->Update();
        }
    }

    void EngineApp::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(EngineApp::OnWindowCloseEvent));

        for(auto it = m_layerStack.end(); it != m_layerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.handled)
            {
                break;
            }
        }
    }

    void EngineApp::PushLayer(Layer* layer)
    {
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void EngineApp::PushOverlay(Layer* layer)
    {
        m_layerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    bool EngineApp::OnWindowCloseEvent(WindowCloseEvent& e)
    {
        m_isRunning = false;
        return true;
    }
}
