#include <Engine.h>
#include <Engine/EngineEntryPoint.h>

#include "TestLayer.h"

class Application : public Engine::EngineApp
{
    public:
        Application()
        {
            PushLayer(new TestLayer());
        }

        ~Application() {}
}; 

Engine::EngineApp* Engine::CreateApplication()
{
    return new Application();
}