#pragma once
#include "api.h"
#include <Windows.h>
#include "OPlus/OPlus.h"
#include <exception>

static HWND hmWnd = nullptr;

#define ShowErrorMessage(message) onyxengine::ShowError(hmWnd, "Engine", message, 1, NULL)
#define ShowErrorMessageDetails(message, details) onyxengine::ShowError(hmWnd, "Engine", message, 1, details)