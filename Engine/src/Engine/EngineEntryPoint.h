#ifndef __ENGINEENTRY_H__
#define __ENGINEENTRY_H__

#include "EngineApp.h"
#include "Logging.h"

extern Engine::EngineApp* Engine::CreateApplication();

int main(int argc, char** argv)
{
    Engine::Log::Init();
    
    auto app = Engine::CreateApplication();
    app->Run();
    delete app;
    
    return 0;
}

#endif