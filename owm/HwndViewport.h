#pragma once

#include <Windows.h>

namespace onyxengine
{
	class HwndViewport
	{
	public:
		HwndViewport(HWND Parent, int Width, int Height);
		~HwndViewport();

		HWND GetHandle();

	private:
		HWND Handle;
	};
}