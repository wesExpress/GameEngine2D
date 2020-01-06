#include "App.h"

#include <GLFW/glfw3.h>

App::App()
:
m_window(new Window())
{
    m_window->Create();
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