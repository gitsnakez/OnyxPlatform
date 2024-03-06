#include "SystemUtilities.h"

namespace onyxengine
{
	Rectangle SystemUtilities::GetPrimaryScreenSize()
	{ return Rectangle(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)); }
}