#pragma once

#include "api.h"
#include <Windows.h>

namespace onyxengine
{
	EXTERN API class HwndViewport
	{
	public:
		HwndViewport(HWND Parent, int Width, int Height);
		~HwndViewport();

		API HWND GetHandle();

	private:
		HWND Handle;
	};
}