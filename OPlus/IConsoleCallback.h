#pragma once
#include <string>

namespace onyxengine
{
    __interface IConsoleCallback
    {
    public:
        virtual void SendCommand(std::string* command) = 0;
        virtual void SendCommand(std::string* command, int parameter) = 0;
        virtual void SendCommand(std::string* command, float parameter) = 0;
        virtual void SendCommand(std::string* command, std::string* parameter) = 0;
    };
}