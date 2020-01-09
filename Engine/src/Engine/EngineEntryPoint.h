#ifndef __ENGINEENTRY_H__
#define __ENGINEENTRY_H__

#include "EngineApp.h"
#include "Logging.h"

extern EngineApp* CreateApplication();

int main(int argc, char** argv)
{
    Log::Init();
    
    auto app = CreateApplication();
    app->Run();
    delete app;
    
    return 0;
}

#endif