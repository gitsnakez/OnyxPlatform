#include "OPlus.h"
#include <Windows.h>

using namespace System;
using namespace System::Windows;
using namespace OSharp;

namespace onyxengine
{
	EXTERN API bool LoadOPlusLibrary()
	{
		return true;
	}
	EXTERN API void SetIsNewTerminal(bool isNew)
	{
		isNewTerminal = isNew;
	}

	EXTERN API bool GetIsNewTerminal()
	{
		return isNewTerminal;
	}

	EXTERN API void ShowError(HWND hmWnd, const char* caption, const char* message, int type, const char* details)
	{
		MessageWindow::Show(IntPtr(hmWnd), gcnew String(caption), gcnew String(message), type, gcnew String(details));
	}

	EXTERN API void SetupCallbacks(IConsoleCallback* callback)
	{
		consWrapper = new ConsoleCallbackWrapper();
		consWrapper->transConsoleCallback = gcnew TransConsoleCallback();
		consWrapper->transConsoleCallback->_pCallBack = callback;
		OSharp::Console::Callback = consWrapper->transConsoleCallback.get();
	}

	EXTERN API void SendBuildInfo(const char *compl_time)
	{
		TerminalMillenium::terminal->buildTime = gcnew System::String(compl_time);
	}
	
	EXTERN API void OpenTerminal()
	{
		ITerminal^ terminal;
		if(isNewTerminal)
			terminal = TerminalWindow::terminal;
		else
			terminal = TerminalMillenium::terminal;

		if (terminal->CheckVisible)
			terminal->SetVisibility(false);
		else
			terminal->SetVisibility(true);
	}
	
	EXTERN API void HideTerminal()
	{
		ITerminal^ terminal;
		if (isNewTerminal)
			terminal = TerminalWindow::terminal;
		else
			terminal = TerminalMillenium::terminal;
		
		terminal->SetVisibility(false);
	}
}