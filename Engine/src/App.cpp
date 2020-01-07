#include "App.h"
#include <GLFW/glfw3.h>

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
        //glClearColor(1, 0, 1, 1);
        //glClear(GL_COLOR_BUFFER_BIT);
        m_window->Update();
    }
}

void App::OnEvent(Event& e)
{
    LOG_TRACE("{0}", e);
}

void App::OnWindowCloseEvent(WindowCloseEvent& e)
{
    m_isRunning = false;
}