#pragma once

#include "api.h"
#include <Windows.h>
#include <locale>
#include <iostream>
#include <fstream>
#include <filesystem>

EXTERN API HRESULT CheckIsFileExsits(LPCWSTR filename, LPCWSTR* msg = nullptr, bool ShowMsgBox = false);