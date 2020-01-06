#include "App.h"
#include "Logging.h"
#include "Window.h"

int main(int argc, char** argv)
{
    Log::Init();
    
    App app = App();
    app.Run();
    
    return 0;
}