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

	void WindowCallback::OnUpdate()
	{
		auto currentTime = std::chrono::steady_clock::now();
		auto elapsed = previousTime - currentTime;


		if (vp != nullptr) vp->OnUpdate();

		float elapsed_f = elapsed.count();


		if (vp != nullptr) vp->m_delta_time = elapsed_f;

		previousTime = currentTime;
	}

	void WindowCallback::OnResize()
	{
		if (vp != nullptr) vp->OnResize();
	}

	void WindowCallback::OnChangePosition()
	{
		if (vp != nullptr) vp->OnChangeLocation();
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