#include <msclr\auto_gcroot.h>
#include "OnyxAPIWrapper.h"
#include "OSharp.h"
#include "IInputSystem.h"
#include "IWindowCallBack.h"
#include <string>

using namespace System::Runtime::InteropServices;
using namespace OSharp;

OnyxAPIWrapper::OnyxAPIWrapper(HWND Handle)
{
    Engine::WindowHandle = (System::IntPtr)Handle;
    Engine::CallBack = gcnew IWindowCallBack();
    Engine::Input = gcnew IInputSystem();
}

OnyxAPIWrapper::~OnyxAPIWrapper()
{

}

void OnyxAPIWrapper::OnCreate()
{
    //_private->engine->OnCreate();
    Engine::OnCreate();
}

void OnyxAPIWrapper::OnUpdate()
{
    //_private->engine->OnUpdate();
    Engine::OnUpdate();
}

void OnyxAPIWrapper::OnDestroy()
{
    //_private->engine->OnDestroy();
    Engine::OnDestroy();
}

void OnyxAPIWrapper::OnResizeWindow()
{
    //_private->engine->OnResizeWindow();
    Engine::OnResizeWindow();
}

void OnyxAPIWrapper::OnChangeWindowPosition()
{
    //_private->engine->OnChangeWindowPosition();
    Engine::OnChangeWindowPosition();
}

void OnyxAPIWrapper::OnEnter()
{
    //_private->engine->OnEnter();
    Engine::OnEnter();
}

void OnyxAPIWrapper::OnLeave()
{
    //_private->engine->OnLeave();
    Engine::OnLeave();
}

void OnyxAPIWrapper::ShowMessage(std::string title, std::string message)
{
    System::String^ titleCLR = gcnew System::String(title.c_str(), 0, title.length());
    System::String^ messageCLR = gcnew System::String(message.c_str(), 0, message.length());
    MessageSystem::Show(titleCLR, messageCLR);
}

void OnyxAPIWrapper::OnKeyDown(int keyCode)
{
    //_private->engine->OnKeyDown(keyCode);
    Engine::OnKeyDown(keyCode);
}

void OnyxAPIWrapper::OnKeyUp(int keyCode)
{
    //_private->engine->OnKeyUp(keyCode);
    Engine::OnKeyUp(keyCode);
}

void OnyxAPIWrapper::OnMouseMove(int X, int Y)
{
    //_private->engine->OnMouseMove(X, Y);
    Engine::OnMouseMove(X, Y);
}

void OnyxAPIWrapper::OnMouseButtonDown(bool isLeftButton, int X, int Y)
{
    //_private->engine->OnMouseButtonDown(isLeftButton, X, Y);
    Engine::OnMouseButtonDown(isLeftButton, X, Y);
}

void OnyxAPIWrapper::OnMouseButtonUp(bool isLeftButton, int X, int Y)
{
    //_private->engine->OnMouseButtonUp(isLeftButton, X, Y);
    Engine::OnMouseButtonUp(isLeftButton, X, Y);
}
