#pragma once

#include "api.h"
#include <Windows.h>

EXTERN API HRESULT CheckIsFileExsits(LPCWSTR filename, LPCWSTR* msg = nullptr, bool ShowMsgBox = false);