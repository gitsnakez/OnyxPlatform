#pragma once

#define WIN32_LEAN_AND_MEAN      // Exclude rarely-used stuff from Windows headers
#include <windows.h>

#ifdef _USRDLL
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif

#define EXTERN extern "C"