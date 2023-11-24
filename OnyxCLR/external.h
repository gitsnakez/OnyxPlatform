#pragma once

#ifdef _WINDLL
#define EXTERNAL extern "C" __declspec(dllexport)
#define EXTERNALDLL __declspec(dllexport)
#else
#define EXTERNAL extern "C" __declspec(dllimport)
#define EXTERNALDLL __declspec(dllimport)
#endif