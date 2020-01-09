#include <Engine.h>
#include <Engine/EngineEntryPoint.h>

class Application : public Engine::EngineApp
{
    public:
        Application()
        {
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