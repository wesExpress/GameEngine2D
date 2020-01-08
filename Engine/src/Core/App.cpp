#include "App.h"
#include "Event/WindowEvent.h"
#include "ImGui/ImGuiLayer.h"

#include <glad/glad.h>

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

App* App::m_instance = nullptr;

App::App()
{
    if (m_instance != nullptr)
    {
        LOG_ERROR("App already exists!");
    }
    else
    {
        m_instance = this;
    }
    
    m_window = std::unique_ptr<Window>(Window::Create());
    m_window->SetEventCallback(BIND_FN(App::OnEvent));

    PushOverlay(new ImGuiLayer());
}

void App::Run()
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

void App::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    LOG_INFO(e.ToString());

    dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(App::OnWindowCloseEvent));

    for(auto it = m_layerStack.end(); it != m_layerStack.begin(); )
    {
        (*--it)->OnEvent(e);
        if (e.handled)
        {
            break;
        }
    }
}

void App::PushLayer(Layer* layer)
{
    m_layerStack.PushLayer(layer);
    layer->OnAttach();
}

void App::PushOverlay(Layer* layer)
{
    m_layerStack.PushOverlay(layer);
    layer->OnAttach();
}

bool App::OnWindowCloseEvent(WindowCloseEvent& e)
{
    m_isRunning = false;
    return true;
}