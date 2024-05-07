#pragma once
#include "api.h"
#include <Windows.h>

EXTERN API bool SetDwmColorWindowAttribute(HWND Handle, int attribute, UINT red, UINT green, UINT blue);
EXTERN API bool SetDwmModeWindowAttribute(HWND Handle, int attribute, int value);
EXTERN API void SetClassicWindowCaption(HWND Handle, bool switcher);

bool BooleanFromHResult(HRESULT hResult);