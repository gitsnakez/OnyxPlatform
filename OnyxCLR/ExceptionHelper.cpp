#include "ExceptionHelper.h"
#include "OnyxAPIWrapper.h"
#include <exception>

void ExceptionHelper::ThrowException(std::string message, std::string title)
{
	OnyxAPIWrapper::ShowMessage(title, message);
	#ifdef _DEBUG
	throw std::exception(message.c_str());
	#endif
	return;
}