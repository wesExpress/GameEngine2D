#include "App.h"

#define BIND_EVENT(x) std::bind(&x, this, std::placeholders::_1)

App::App()
:
m_window(new Window())
{
    m_window->Create();
    m_window->SetEventCallback(BIND_EVENT(App::OnEvent));
}

void App::Run()
{
    while(m_isRunning)
    {
        m_window->Update();
    }
}

void App::OnEvent(Event& e)
{
    LOG_INFO(e.ToString());
    if (e.GetEventType() == WindowCloseEvent::GetStaticType())
    {
        OnWindowCloseEvent();
    }
}

void App::OnWindowCloseEvent()
{
    m_isRunning = false;
}