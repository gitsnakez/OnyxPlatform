#include "engine.h"

EXTERN API void* CreateEngine()
{
    return (void*) new GraphicsEngine();
}

EXTERN API void* CreateViewport(void* hWnd, void* engine)
{
    return (void*) new Viewport(hWnd, engine);
}

EXTERN API void OnCreateViewport(void* viewport)
{
    ((Viewport*)viewport)->OnCreate();
}