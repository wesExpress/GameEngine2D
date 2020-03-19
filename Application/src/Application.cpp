#include <Engine.h>
#include <Engine/EngineEntryPoint.h>

#include "TestLayer.h"
#include "Sandbox2D.h"

class Application : public Engine::EngineApp
{
    public:
        Application()
        {
            //PushLayer(new TestLayer());
            PushLayer(new Sandbox2D());
        }

        ~Application() {}
}; 

Engine::EngineApp* Engine::CreateApplication()
{
    return new Application();
}