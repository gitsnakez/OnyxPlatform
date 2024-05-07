#pragma once
#include "api.h"
#include <Roapi.h>
#include <Windows.h>
#include "OPlus/OPlus.h"
#include <exception>

#define NULLSTR ""

enum ONERRDISP
{
	OED_MESSAGE = 0,
	OED_ERROR = 1,
};

namespace onyxengine
{
	void ShowSteamErrorMessage(std::string message)
	{
		if (message == std::string("ConnectToGlobalUser failed."))
			ShowError(NULL, "Steam", "Application failed to start!\n1. You have no game.\n2. Your steam in family mode now.", ONERRDISP::OED_ERROR, message.c_str());
		else if (message == std::string("Cannot create IPC pipe to Steam client process.  Steam is probably not running."))
			ShowError(NULL, "Steam", "Application failed to start!\n1. Steam process isn't running.", ONERRDISP::OED_ERROR, message.c_str());
		else
			ShowError(NULL, "Engine", message.c_str(), ONERRDISP::OED_ERROR, NULLSTR);
	}

	void ShowErrorMessage(std::string message, std::string title, std::string details)
	{
		if(title == NULLSTR)
			ShowError(NULL, "Engine", message.c_str(), ONERRDISP::OED_ERROR, details.c_str());
		else
			ShowError(NULL, title.c_str(), message.c_str(), ONERRDISP::OED_ERROR, details.c_str());

	}

	void ShowOnyxMessage(std::string message, std::string title)
	{
		if (title == NULLSTR)
			ShowError(NULL, "Engine", message.c_str(), ONERRDISP::OED_MESSAGE, NULLSTR);
		else
			ShowError(NULL, title.c_str(), message.c_str(), ONERRDISP::OED_MESSAGE, NULLSTR);

	}
}