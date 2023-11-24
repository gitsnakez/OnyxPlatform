#pragma once

//
#ifdef DLLAPP
#define shared_method extern "C" __declspec(dllexport)
#else
#define shared_method extern "C" __declspec(dllimport)
#endif // shared_method