#pragma once
#include "ViewportBaseRes.h"

__interface IViewportObject
{
	void InitializeDesc(VPDESC* gDesc);
	void InitializeDesc(VPDESC* gDesc, VPADESC* aDesc);
	void InitializeDesc(VPDESC* gDesc, VPEXDESC* exDesc);
	void InitializeDesc(VPDESC* gDesc, VPADESC* aDesc, VPEXDESC* exDesc);
	
	bool IsRunning();

	// Desktop
	void OnCreate();
	void OnUpdate();
	void OnDestroy();
	void OnResize();
	void SetFullscreen();
	void OnChangePosition();
	void OnEnter();
	void OnLeave();

	// Keyboard
	void OnKeyDown(int key);
	void OnKeyUp(int key);

	// Mouse
	void OnMouseMove(VEC2D delta_mouse_pos);
	void OnMouseLeftButtonDown(VEC2D delta_mouse_pos);
	void OnMouseLeftButtonUp(VEC2D delta_mouse_pos);
	void OnMouseRightButtonDown(VEC2D delta_mouse_pos);
	void OnMouseRightButtonUp(VEC2D delta_mouse_pos);

	VPH GetHandle();
};