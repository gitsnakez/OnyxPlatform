#pragma once

#include "api.h"
#include "GraphicsEngine.h"
#include "Viewport.h"

EXTERN API void* CreateEngine();
EXTERN API void* CreateViewport(void* hWnd, void* engine, bool isBorder);
EXTERN API void OnCreateViewport(void* viewport);