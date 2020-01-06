#ifndef __APP_H__
#define __APP_H__

#include <memory>

#include "Logging.h"
#include "Window.h"

class App
{
    public:
        App();

        void Run();

    private:
        bool m_isRunning = true;
        std::unique_ptr<Window> m_window;
};

#endif