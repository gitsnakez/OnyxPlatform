#include "engine.h"

EXTERN API void* CreateEngine()
{
    return (void*) new GraphicsEngine();
}

EXTERN API void* CreateViewport(void* hWnd, void* engine, bool isBorder)
{
    return (void*) new Viewport(hWnd, engine, isBorder);
}

EXTERN API void OnCreateViewport(void* viewport)
{
    ((Viewport*)viewport)->OnCreate();
}