#pragma once
#include <Windows.h>
#include "pch.h"
#include "share.h"

EXTERN API int ExternMain()
{
	MessageBox(NULL, L"This is test library message", L"Test Library", MB_OK);

	return 0;
}