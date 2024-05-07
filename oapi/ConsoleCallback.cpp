#include "ConsoleCallback.h"
#include "Window.h"
#include "Viewport.h"
#include "GraphicsEngine.h"
#include "OPlus/OPlus.h"
#include <Windows.h>
#include <sstream>

namespace onyxengine
{
	void ConsoleCallback::SendCommand(std::string* command)
	{
		if (*command == "quit")
			((Window*)hDesc->hWin)->Exit();
		else if (*command == "to_zero_pos")
		{
			((Viewport*)hDesc->hViewPort)->GoToZeroPos();
		}
		else if (*command == "unload_map")
		{
			((Viewport*)hDesc->hViewPort)->UnloadLevel();
		}
	}

	void ConsoleCallback::SendCommand(std::string* command, int parameter)
	{
		if (*command == "showpos")
		{
			((Viewport*)hDesc->hViewPort)->ShowPos(&parameter);
		}
		else if (*command == "showgraph")
		{
			((Viewport*)hDesc->hViewPort)->ShowGraph(&parameter);
		}
		else if (*command == "showhud")
		{
			((Viewport*)hDesc->hViewPort)->ShowHud(&parameter);
		}
		else if (*command == "sensetivity")
		{
			_pController->sensetivity = (float)parameter;
		}
		else if (*command == "vsync")
		{
			bool param_bool = (parameter >= 1) ? true : false;
			((Viewport*)hDesc->hViewPort)->SetVSync(param_bool);
		}
		else if (*command == "new_terminal")
		{
			bool param_bool = (parameter >= 1) ? true : false;
			if (GetIsNewTerminal() == param_bool)
				return;

			HideTerminal();

			if (param_bool) SetIsNewTerminal(true);
			else SetIsNewTerminal(false);

			OpenTerminal();
		}
		else if (*command == "mat_wireframe")
		{
			bool param_bool = (parameter >= 1) ? true : false;

			((Viewport*)hDesc->hViewPort)->SetWireframeMode(param_bool);
		}
	}

	void ConsoleCallback::SendCommand(std::string* command, float parameter)
	{
		if (*command == "sensetivity")
			_pController->sensetivity = parameter;
	}

	void ConsoleCallback::SendCommand(std::string* command, std::string* param)
	{
		if (*command == "map")
		{
			((Viewport*)hDesc->hViewPort)->UnloadLevel();
			auto builder = std::wstringstream();
			builder << L"maps/" << param->c_str() << L".level";
			//((Viewport*)hDesc->hViewPort)->LoadLevel(builder.str().c_str());
			LoadLevelAPI(builder.str().c_str(), ((Viewport*)hDesc->hViewPort));
		}
	}
}