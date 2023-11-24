#pragma once
#include <string>

class ExceptionHelper
{
public:
	static void ThrowException(std::string message, std::string title);
};