#include "WindowWorks.h"
#include "dwmapi.h"

EXTERN API bool SetDwmColorWindowAttribute(HWND Handle, int attribute, UINT red, UINT green, UINT blue)
{
	COLORREF value = RGB(red, green, blue);

	return BooleanFromHResult(
		DwmSetWindowAttribute(Handle, attribute, &value, sizeof(COLORREF))
	);
}

EXTERN API bool SetDwmModeWindowAttribute(HWND Handle, int attribute, int value)
{
	HRESULT hResult = S_FALSE;

	switch (attribute)
	{
		//
		// Set title dark mode
		case DWMWA_USE_IMMERSIVE_DARK_MODE:
			if ((hResult = DwmSetWindowAttribute(Handle, 19, &value, sizeof(int))) != 0)
				hResult = DwmSetWindowAttribute(Handle, 20, &value, sizeof(int));
		break;


		//
		// Set corner type
		case DWMWA_WINDOW_CORNER_PREFERENCE:
			hResult = DwmSetWindowAttribute(Handle, DWMWA_WINDOW_CORNER_PREFERENCE, &value, sizeof(int));
		break;
	}

	return BooleanFromHResult(hResult);
}

EXTERN API void SetClassicWindowCaption(HWND Handle, bool switcher)
{
	if(switcher)
		SetWindowTheme(Handle, NULL, L"CLASSIC");
	else
		SetWindowTheme(Handle, NULL, L"");

	int rectCorner = (bool)switcher;
	DwmSetWindowAttribute(Handle, DWMWA_WINDOW_CORNER_PREFERENCE, &rectCorner, sizeof(int));
}

bool BooleanFromHResult(HRESULT hResult)
{
	switch (hResult)
	{
		case S_OK:
		return true;

		default:
		return false;
	}
}