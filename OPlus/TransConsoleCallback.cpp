#include "TransConsoleCallback.h"
#include <string>

namespace onyxengine
{
    void MarshalString(String^ s, std::string& os) {
        using namespace Runtime::InteropServices;
        const char* chars =
            (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
        os = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }

    void TransConsoleCallback::SendCommand(String^ command)
    {
        std::string* cmd = new std::string();
        MarshalString(command, *cmd);
        _pCallBack->SendCommand(cmd);
    }

    void TransConsoleCallback::SendCommand(String^ command, int parameter)
    {
        std::string* cmd = new std::string();
        MarshalString(command, *cmd);
        _pCallBack->SendCommand(cmd, parameter);
    }

    void TransConsoleCallback::SendCommand(String^ command, float parameter)
    {
        std::string* cmd = new std::string();
        MarshalString(command, *cmd);
        _pCallBack->SendCommand(cmd, parameter);
    }

    void TransConsoleCallback::SendCommand(String^ command, String^ parameter)
    {
        std::string* cmd = new std::string();
        std::string* param = new std::string();
        MarshalString(command, *cmd);
        MarshalString(parameter, *param);
        _pCallBack->SendCommand(cmd, param);
    }
}