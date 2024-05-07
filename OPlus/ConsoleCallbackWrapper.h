#pragma once
#include "api.h"
#include <msclr/auto_gcroot.h>
#include "TransConsoleCallback.h"
#include "IConsoleCallback.h"
#include "OSharpUse.h"

using namespace System;
using namespace OSharp;

namespace onyxengine
{
	class ConsoleCallbackWrapper
	{
	public:
		ConsoleCallbackWrapper();
		msclr::auto_gcroot<TransConsoleCallback^> transConsoleCallback;
	};
}