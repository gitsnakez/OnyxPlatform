#include "WindowCallback.h"
#include "isteamfriends.h"
#include "ConvertChars.h"
#include "OPlus/OPlus.h"
#include "ToolViewport.h"
#include <string>

namespace onyxengine
{
	WindowCallback::WindowCallback(HDESC* DescHandler, Controller* control)
	{
		hDesc = DescHandler;
		ct = control;
	}

	WindowCallback::WindowCallback()
	{
	}

	void WindowCallback::OnCreate()
	{
		auto compl_time = std::stringstream();
		compl_time << __DATE__ << " - " << __TIME__;
		SendBuildInfo(compl_time.str().c_str());

		((ToolViewport*)hDesc->hViewPort)->OnCreate();
		((Window*)hDesc->hWin)->engineinited = true;
	}

	void WindowCallback::OnClosing(bool* isCancle)
	{
	}

	void WindowCallback::OnUpdate()
	{
		// Counts Per Second
		INT64 counts_per_sec = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&counts_per_sec);
		// Seconds Per Count
		float sec_per_count = 1.0f / (float)counts_per_sec;
		// Pervious Time
		INT64 prev_time = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&prev_time);

		ControllerUpdate();

		// Final update
		if ((ToolViewport*)hDesc->hViewPort != nullptr)
			((ToolViewport*)hDesc->hViewPort)->UpdateViewport(deltatime);

		Sleep(1);

		// Get current count
		INT64 current_time = 0;
		QueryPerformanceCounter((LARGE_INTEGER*)&current_time);

		// DeltaTime
		deltatime = (current_time - prev_time) * sec_per_count;

		// Delta time define (OLD IMPLEMENTATION)
		//old_delta = new_delta;
		//new_delta = GetTickCount64();
		//
		//deltatime = (old_delta) ? ((new_delta - old_delta) / 1000.0f) : 0;
	}

	void WindowCallback::ControllerUpdate()
	{
		if (ct == nullptr)
			return;

		ct->deltatime = deltatime;
		// Input
		if (ct->playmode)
		{
			ct->camx = Math::Lerp(ct->oldrotx, ct->rotx, deltatime * 50);
			ct->camy = Math::Lerp(ct->oldroty, ct->roty, deltatime * 50);
			ct->oldrotx = ct->camx;
			ct->oldroty = ct->camy;
			//UpdateMovementParameters((ToolViewport*)hDesc->hViewPort, ct->forward, ct->rightward);
			//UpdateRotateParameters((ToolViewport*)hDesc->hViewPort, ct->camx, ct->camy);
			ct->forward = 0;
			ct->rightward = 0;

			ct->forward = 0;
			ct->rightward = 0;

			if (ct->isSlow)
				ct->movespeed = 0.05f;
			else if (ct->isSprint)
				ct->movespeed = 0.5f;
			else
				ct->movespeed = 0.2f;
		}
		else
		{
			ct->camx = ct->oldrotx;
			ct->camy = ct->oldroty;
		}
	}

	void WindowCallback::OnResize(const Rectangle& size)
	{
		if (ct->useBorders)
			if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnResize(size.Width - 16, size.Height - 39); else;
		else
			if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnResize(size.Width, size.Height); else;
	}

	void WindowCallback::OnChangePosition(const Point& location)
	{
		if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnChangeLocation(location.X, location.Y);
	}

	void WindowCallback::OnDestroy()
	{
		if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnDestroy();
	}

	void WindowCallback::OnEnter()
	{
		if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnEnter();
	}

	void WindowCallback::OnLeave()
	{
		if ((ToolViewport*)hDesc->hViewPort != nullptr) ((ToolViewport*)hDesc->hViewPort)->OnLeave();
	}

	void WindowCallback::OnKeyDown(int key)
	{
		if (ct != nullptr) ct->OnKeyDown(key);
	}

	void WindowCallback::OnKeyUp(int key)
	{
		if (ct != nullptr) ct->OnKeyUp(key);
	}

	void WindowCallback::OnMouseMove(const Point& delta_mouse_pos)
	{
		if (ct != nullptr) ct->OnMouseMove(delta_mouse_pos);
	}

	void WindowCallback::OnMouseLeftButtonDown(const Point& delta_mouse_pos)
	{
		if (ct != nullptr) ct->OnMouseLeftButtonDown(delta_mouse_pos);
	}

	void WindowCallback::OnMouseLeftButtonUp(const Point& delta_mouse_pos)
	{
		if (ct != nullptr) ct->OnMouseLeftButtonUp(delta_mouse_pos);
	}

	void WindowCallback::OnMouseRightButtonDown(const Point& delta_mouse_pos)
	{
		if (ct != nullptr) ct->OnMouseRightButtonDown(delta_mouse_pos);
	}

	void WindowCallback::OnMouseRightButtonUp(const Point& delta_mouse_pos)
	{
		if (ct != nullptr) ct->OnMouseRightButtonUp(delta_mouse_pos);
	}
}