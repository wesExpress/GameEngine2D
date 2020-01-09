#include <Engine.h>
#include <Engine/EngineEntryPoint.h>

class Application : public EngineApp
{
    public:
        Application()
        {
            PushOverlay(new ImGuiLayer());
        }

        ~Application()
        {

        }
}; 

EngineApp* CreateApplication()
{
    return new Application();
}