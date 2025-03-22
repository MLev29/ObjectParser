#include "Window.h"
#include "tools/Timer.h"
#include "tools/MemoryCheck.h"

int main(void)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    objParser::Engine engine({960, 540});

    if (engine.Init())
        return -1;

    while (!glfwWindowShouldClose(engine.GetWindowPtr()))
    {
        engine.Update(objParser::DeltaTime());
    }

    engine.Shutdown();

    _CrtDumpMemoryLeaks();

    return 0;
}