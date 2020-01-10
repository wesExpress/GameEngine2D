#include "EngineApp.h"
#include "Event/WindowEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Input.h"

#include <glad/glad.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace Engine
{
    EngineApp* EngineApp::m_instance = nullptr;

    EngineApp::EngineApp()
    {
        if (m_instance != nullptr)
        {
            ENGINE_ERROR("App already exists!");
        }
        else
        {
            m_instance = this;
        }
        
        m_window = std::unique_ptr<Window>(Window::Create());
        m_window->SetEventCallback(BIND_FN(EngineApp::OnEvent));
    }

    void EngineApp::Run()
    {
        while(m_isRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            
            for (Layer* layer : m_layerStack)
            {
                layer->OnUpdate();
            }

            m_window->Update();
        }
    }

    void EngineApp::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);

        //ENGINE_INFO(e.ToString());

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