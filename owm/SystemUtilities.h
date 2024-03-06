#pragma once

#include <Windows.h>
#include "api.h"
#include "Standart.h"

namespace onyxengine
{
	EXTERN static class API SystemUtilities
	{
	public:
		static Rectangle GetPrimaryScreenSize();
	};
}