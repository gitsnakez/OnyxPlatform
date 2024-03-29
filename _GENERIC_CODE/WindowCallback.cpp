#include "WindowCallback.h"

namespace onyxengine
{
	WindowCallback::WindowCallback(HDESC* hDesc, Controller* control)
	{
		vp = (Viewport*)(hDesc->hViewPort);
		ct = control;
	}

	WindowCallback::WindowCallback()
	{
	}

	void WindowCallback::OnCreate()
	{
		if (vp != nullptr) vp->OnCreate();
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

		// Input
		if (ct->playmode)
		{
			ct->camx = Math::Lerp(ct->oldrotx, ct->rotx, deltatime * 50);
			ct->camy = Math::Lerp(ct->oldroty, ct->roty, deltatime * 50);
			ct->oldrotx = ct->camx;
			ct->oldroty = ct->camy;
			UpdateMovementParameters(vp, ct->forward, ct->rightward);
			UpdateRotateParameters(vp, ct->camx, ct->camy);
			ct->forward = 0;
			ct->rightward = 0;

			ct->forward = 0;
			ct->rightward = 0;

			if(ct->isSlow)
				ct->movespeed = 0.05f;
			else if (ct->isSprint)
				ct->movespeed = 0.5f;
			else
				ct->movespeed = 0.2f;
			/*
			if (ct->movespeed < 0.2f)
				ct->movespeed = Math::Lerp(ct->movespeed, 0.21f, deltatime * 2);*/
		}
		else
		{
			ct->camx = ct->oldrotx;
			ct->camy = ct->oldroty;
		}

		// Final update
		if (vp != nullptr)
		{
			vp->m_delta_time = deltatime;
			vp->OnUpdate();
		}
		if (vp != nullptr) vp->m_delta_time = deltatime;
		ct->deltatime = deltatime;

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

	void WindowCallback::OnResize(const Rectangle& size)
	{
		if (ct->useBorders)
			if (vp != nullptr) vp->OnResize(size.Width - 16, size.Height - 39); else;
		else
			if (vp != nullptr) vp->OnResize(size.Width, size.Height); else;
	}

	void WindowCallback::OnChangePosition(const Point& location)
	{
		if (vp != nullptr) vp->OnChangeLocation(location.X, location.Y);
	}

	void WindowCallback::OnDestroy()
	{
		if (vp != nullptr) vp->OnDestroy();
	}

	void WindowCallback::OnEnter()
	{
		if (vp != nullptr) vp->OnEnter();
	}

	void WindowCallback::OnLeave()
	{
		if (vp != nullptr) vp->OnLeave();
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