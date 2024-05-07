#pragma once

#include "OPlus/IConsoleCallback.h"
#include "IWindowCallback.h"
#include "Controller.h"
#include "defs.h"
#include <string>

namespace onyxengine
{
    class ConsoleCallback : public IConsoleCallback
    {
    public:
        virtual void SendCommand(std::string* command);
        virtual void SendCommand(std::string* command, int parameter);
        virtual void SendCommand(std::string* command, float parameter);
        virtual void SendCommand(std::string* command, std::string* parameter);

        HDESC* hDesc;
        IWindowCallback* _pWndCallback;
        Controller* _pController;
    };
}