#ifndef __ENGINEAPP_H__
#define __ENGINEAPP_H__

#include "Logging.h"
#include "Window.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"
#include "LayerStack.h"

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

        bool m_isRunning = true;
        std::unique_ptr<Window> m_window;
        LayerStack m_layerStack;      
        static EngineApp* m_instance;
};

#endif