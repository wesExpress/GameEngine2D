#include "App.h"
#include "Event/WindowEvent.h"

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)

App::App()
:
m_window(new Window())
{
    m_window->Create();
    m_window->SetEventCallback(BIND_FN(App::OnEvent));
}

void App::Run()
{
    while(m_isRunning)
    {
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        
        m_window->Update();

        for (Layer* layer : m_layerStack)
        {
            layer->OnUpdate();
        }
    }
}

void App::OnEvent(Event& e)
{
    EventDispatcher dispatcher(e);

    LOG_INFO(e.ToString());

    dispatcher.Dispatch<WindowCloseEvent>(BIND_FN(App::OnWindowCloseEvent));

    for(auto it = m_layerStack.rbegin(); it != m_layerStack.rend(); ++it )
    {
        (*it)->OnEvent(e);
        if (e.handled)
        {
            break;
        }
    }
}

void App::PushLayer(Layer* layer)
{
    m_layerStack.PushLayer(layer);
}

void App::PushOverlay(Layer* layer)
{
    m_layerStack.PushOverlay(layer);
}

bool App::OnWindowCloseEvent(WindowCloseEvent& e)
{
    m_isRunning = false;
    return true;
}