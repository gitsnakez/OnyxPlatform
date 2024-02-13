#pragma once

#include "external.h"
#include <Windows.h>
#include <string>

class EXTERNALDLL OnyxAPIWrapper
{
public:
	OnyxAPIWrapper(HWND Handle);
	~OnyxAPIWrapper();

	// Window Events
	void OnCreate();
	void OnUpdate();
	void OnDestroy();
	void OnResizeWindow();
	void OnChangeWindowPosition();
	void OnEnter();
	void OnLeave();
	static void ShowMessage(std::string title, std::string message);

	// Input Events
	void OnKeyDown(int keyCode);
	void OnKeyUp(int keyCode);
	void OnMouseMove(int X, int Y);
	void OnMouseButtonDown(bool isLeftButton, int X, int Y);
	void OnMouseButtonUp(bool isLeftButton, int X, int Y);
};