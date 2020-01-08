#ifndef __APP_H__
#define __APP_H__

#include "Logging.h"
#include "Window.h"
#include "Event/Event.h"
#include "Event/WindowEvent.h"
#include "LayerStack.h"

class App
{
    public:
        App();

        void Run();
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline Window& GetWindow() const { return *m_window; }
        static App& Get() {return *m_instance; };

    private:
        bool OnWindowCloseEvent(WindowCloseEvent& e);

        bool m_isRunning = true;
        std::unique_ptr<Window> m_window;
        LayerStack m_layerStack;      
        static App* m_instance;
};

#endif