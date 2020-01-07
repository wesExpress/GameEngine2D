#ifndef __APP_H__
#define __APP_H__

#include "Logging.h"
#include "Window.h"
#include "Event/WindowEvent.h"

class App
{
    public:
        App();

        void Run();
        void OnEvent(Event& e);

    private:
        bool m_isRunning = true;
        std::unique_ptr<Window> m_window;

        void OnWindowCloseEvent();
};

#endif