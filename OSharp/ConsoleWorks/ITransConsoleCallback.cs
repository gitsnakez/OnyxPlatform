using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OSharp
{
    public interface ITransConsoleCallback
    {
        void SendCommand(string command);
        void SendCommand(string command, int parameter);
        void SendCommand(string command, float parameter);
        void SendCommand(string command, string parameter);
    }
}