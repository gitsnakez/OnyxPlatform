#include "engine.h"
#include "ToolViewport.h"
#include "ErrorDispatcher.h"

EXTERN API void* CreateEngine()
{
    return (void*) new GraphicsEngine();
}

EXTERN API void* CreateViewport(void* hWnd, void* engine, bool isBorder)
{
    hmWnd = (HWND)(hWnd);
    return (void*) new Viewport(hWnd, engine, isBorder);
}

EXTERN API void* CreateToolViewport(void* hWnd, void* engine)
{
    hmWnd = (HWND)(hWnd);
    return (void*) new ToolViewport(hWnd, engine);
}

EXTERN API void OnCreateViewport(void* viewport)
{
    ((Viewport*)viewport)->OnCreate();
}