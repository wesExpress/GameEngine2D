#include <Engine.h>

class TestLayer : public Engine::Layer
{
    public:
        TestLayer()
        :
        Engine::Layer("Test Layer")
        {}

        void OnUpdate() override
        {
            if(Engine::Input::IsMouseButtonPressed(MOUSE_BUTTON_1))
            {
                CLIENT_INFO("Mouse clicked.");
            }
        }
};

class Application : public Engine::EngineApp
{
    public:
        Application()
        {
            PushLayer(new TestLayer());
            PushOverlay(new Engine::ImGuiLayer());
        }

        ~Application()
        {

        }
}; 

Engine::EngineApp* Engine::CreateApplication()
{
    return new Application();
}