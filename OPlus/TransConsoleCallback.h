#pragma once

#include "OSharpUse.h"
#include "IConsoleCallback.h"

using namespace OSharp;
using namespace System;

namespace onyxengine
{
    public ref class TransConsoleCallback : public OSharp::ITransConsoleCallback
    {
    public:
        virtual void SendCommand(String ^command);
        virtual void SendCommand(String ^command, int parameter);
        virtual void SendCommand(String ^command, float parameter);
        virtual void SendCommand(String ^command, String ^parameter);

        IConsoleCallback* _pCallBack;
    };
}